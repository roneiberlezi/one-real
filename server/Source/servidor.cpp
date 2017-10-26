#if defined(__APPLE__)						// If we are using a mac
    #include <SDL2/SDL_net.h>
    #include <SDL2/SDL.h>
    #define SSCANF sscanf
    #define SPRINTF sprintf
    #define STRCPY strcpy
#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
    #include <SDL_net.h>
    #include <SDL.h>
    #define SSCANF sscanf_s
    #define SPRINTF sprintf_s
    #define STRCPY strcpy_s
#endif

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <map>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Bullet.h"
#include "Player.h"
#include "Collidable.h"
#include "Map.h"
#include "Agent.h"
#include "Item.h"

#define PI 3.14159265

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

const int MAX_SCORE = 5;
const int WAIT_TIME = 10000;//10 seconds wait between rounds
const int ITEM_RESPAWN_TIME = 5;////Time in seconds for the next item respawn
const int NUM_MAPS = 4;

const char* maps[10];

int currentMap = 3;
bool firstBlood = false;
int bulletID = 0;
int itemID = 0;

int lastTimeDataSent = 0;
int PPS_Monster = 15;

bool endGame = false;

char buffer[1400];
int size;

//Id used to identify players and monsters
int idGenerator = 0;
int numberOfPlayers = 0; //Number of players connected
int maxPlayers = 30;

std::vector<Bullet*> bullets;
std::map<int, Player*> players;
std::map<int, Item*> items;

Map* mMap = NULL;

void generateRandomPosition(int* x, int* y);
void sendData(TCPsocket socket);
void sendDataToAllConnectedSockets();
void sendDataToAllConnectedSocketsExceptOne(int id);
void generateNewItem(int* type, int* posX, int* posY, int* iInfo);
bool checkMapCollision(int x, int y, SDL_Rect objectCollisionRect);

int main(int argc, char* args[])
{
    srand (time(NULL));
    maps[0] = "smallmap";
    maps[1] = "map2";
    maps[2] = "map3";
    maps[3] = "map4";
    
    mMap = new Map(maps[currentMap], TILE_WIDTH, TILE_HEIGHT, 0, 0);
    
    
	//CODIGO DO SERVIDOR!
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
    
    int nextRoundTime;
    bool maxScoreReached = false;

	IPaddress ip;

	SDLNet_ResolveHost(&ip, NULL, 1234);

	bool running = true;
    
    int startTimeNetwork = SDL_GetTicks();
    int startTimeItems = SDL_GetTicks();
    int PPS = 30;
    lastTimeDataSent = SDL_GetTicks();
    
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(30);
	
	//Abre o servidor para conexıes
	TCPsocket server = SDLNet_TCP_Open(&ip);

	std::cout << "Server started!";

	while (running){
			//Aceita uma nova conexão, caso nenhuma conexão nova seja criada, ele retornar· NULL em tmpSocket
			TCPsocket tmpSocket = SDLNet_TCP_Accept(server);

			if (tmpSocket){
				if (numberOfPlayers < maxPlayers){
					//Prepara a mensagem de resposta, retornando o id do novo player
                    int x, y;//New position to the connected player
                    generateRandomPosition(&x, &y);
					SPRINTF(buffer, "%d %d %d %d %d \n", MESSAGE_TYPE.NEW_PLAYER, idGenerator, currentMap, x, y);
                    
                    //insert a new player into the server map of players
                    players.insert(std::pair<int, Player*>(idGenerator, new Player(idGenerator, tmpSocket)));
                    SDLNet_TCP_AddSocket(socketSet, players.find(idGenerator)->second->socket);
                    sendData(players.find(idGenerator)->second->socket);
                    
					std::cout << "\n A new connection was made by player id:" << idGenerator << "\n";
                    idGenerator++;
                    numberOfPlayers++;
				}
				else{
					SPRINTF(buffer, "Max connection reached! Try again later!");
					std::cout << "Warning Maximum connections reached! Player is beeing droped!\n";
				}
			}
        
            //Taxa de respawn de itens
            if (SDL_GetTicks() > startTimeItems + (ITEM_RESPAWN_TIME * 1000)) {
                startTimeItems = SDL_GetTicks();
                int itemType, x, y, iInfo;
                
                //SSCANF(tmp, "%d %d %d %d %d %d", &messageType, &itemType, &itemId, &iPosx, &iPosy, &iInfo);
                generateNewItem(&itemType, &x, &y, &iInfo);
                SPRINTF(buffer, "%d %d %d %d %d %d \n", MESSAGE_TYPE.ITEM_SPAWN, itemType, itemID, x, y, iInfo);
                items[itemID] = new Item(itemID, x, y, 35, 35, 1, itemType, iInfo);
                itemID++;
                
                sendDataToAllConnectedSockets();
                
                
                //---------------------------END ROUND-------------------------------------------------------
                //Se um jogador conseguiu 10 kills, termine o round
                if (maxScoreReached && !endGame){
                    endGame = true;
                    nextRoundTime = SDL_GetTicks();
                    
                    //Envia o score de cada jogador para todos os sockets
                    for (std::map<int, Player*>::iterator player = players.begin(); player != players.end(); ++player){
                        //Envia o id do player, e seus valores de kills e deaths para o player que requisitou
                        SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.PLAYER_SCORE, player->second->id, player->second->kills, player->second->deaths);
                        sendDataToAllConnectedSockets();
                    }
                    
                    //Envia mensagem para terminar o round
                    SPRINTF(buffer, "%d \n", MESSAGE_TYPE.ROUND_END);
                    sendDataToAllConnectedSockets();
                }
                //--------------------------------------END ROUND-------------------------------------------------------
                
                
                //-------------------------------------START ROUND-------------------------------------------------------
                
                if (endGame && (SDL_GetTicks() - nextRoundTime) > WAIT_TIME)
                {
                    //Atualiza para o prÛximo mapa
                    currentMap++;
                    if (currentMap >= NUM_MAPS) {
                        currentMap = 0;
                    }
                    
                    mMap->~Map();
                    printf("\nCarregando novo mapa");
                    mMap = new Map(maps[currentMap], TILE_WIDTH, TILE_HEIGHT, 0, 0);
                    
                    endGame = false;
                    maxScoreReached = false;
                    firstBlood = false;
                    
                    for (std::map<int, Player*>::iterator player = players.begin(); player != players.end(); ++player){
                        player->second->initRoundValues();
                        
                        //Envia mensagem para iniciar o round
                        int x, y;
                        generateRandomPosition(&x, &y);
                        SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.ROUND_START, currentMap,x,y);
                        sendData(player->second->socket);
                    }
                    
                    //Zerar vetor de itens
                    items.clear();
                    
                    //Zerar vetor de balas
                    bullets.clear();
                    
                    //Enviar atualizacao de score para todos
                    for (std::map<int, Player*>::iterator player = players.begin(); player != players.end(); ++player){
                        //Envia o score, comando de respawn e o valor de hp de cada player para todos os sockets
                        SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.PLAYER_SCORE, player->second->id, player->second->kills, player->second->deaths);
                        sendDataToAllConnectedSockets();
                        SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.PLAYER_RESPAWN, player->second->id, player->second->position.x, player->second->position.y);
                        sendDataToAllConnectedSockets();
                        SPRINTF(buffer, "%d %d %d \n", MESSAGE_TYPE.PLAYER_HP, player->second->id, player->second->currentHP);
                        sendDataToAllConnectedSockets();
                    }
                    
                    //-------------------------------------START ROUND-------------------------------------------------------
                }
            }
        
            //Taxa de atualizacão das balas
            if((SDL_GetTicks()-startTimeNetwork) > 1000/PPS){
                //calcula o tempo para respawn
                for (std::map<int,Player*>::iterator p = players.begin(); p!=players.end(); ++p){
                    if (!p->second->alive){
                        int diferenceTime = 6 - ((SDL_GetTicks() - p->second->deathTime)/1000);
                        if (diferenceTime <= 0) {
                            p->second->alive = true;
                            p->second->currentHP = 100;
                            
                            int x, y;
                            generateRandomPosition(&x, &y);
                            
                            SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.PLAYER_RESPAWN, p->second->id, x, y);
                            sendDataToAllConnectedSockets();
                        }
                    }
                }
                
                //Send all bullets to all clients
                std::vector<Bullet*>::iterator bullet;
                for (bullet = bullets.begin(); bullet != bullets.end();){
                    
                    //update the next position, before sending it
                    (*bullet)->setPosition(cos(( (*bullet)->angle-180) *( PI/180 ) ) *
                                       ((*bullet)->velocity * ((SDL_GetTicks() - (*bullet)->deltaTime)/1000.0))
                                        , sin( ((*bullet)->angle-180) *( PI/180 ) ) *
                                        ((*bullet)->velocity * ((SDL_GetTicks() - (*bullet)->deltaTime)/1000.0)));
                    
                    (*bullet)->deltaTime = SDL_GetTicks();
                    
                    int x = (int) (*bullet)->x/TILE_WIDTH;
                    int y = (int) (*bullet)->y/TILE_HEIGHT;
                    
                    //if the bullet escapes from map
                    if ((x >= mMap->sizeX || y >= mMap->sizeY) || (x < 0 || y < 0)) {
                        (*bullet)->destroy = true;
                    }else{
                        if (mMap->layer[1]->layer[x][y] != 0)
                            (*bullet)->destroy = true;
                    }
                    
                    if (!(*bullet)->destroy)
                    //check colision with all players
                    for (std::map<int,Player*>::iterator player=players.begin(); player!=players.end();){
                        //If collision occured with a player
                        if (Collidable::checkCollision(player->second->collisionRect, (*bullet)->collisionRect) && !(*bullet)->destroy){
                            //if the player is not himself
                            if ((*bullet)->playerId != player->second->id && player->second->alive){
                                (*bullet)->destroy = true;

								//Diminui o HP de acordo com o tipo de bala
								switch ((*bullet)->type){
									case 0:
										player->second->currentHP -= 15;
                                        break;
									case 1:
										player->second->currentHP -= 20;
										break;
									case 2:
										player->second->currentHP -= 25;
										break;
									case 3:
										player->second->currentHP -= 30;
										break;
                                    case 4:
                                        player->second->currentHP -= 30;
                                        break;
								}

								//Hited player is dead
								if (player->second->currentHP <= 0)
								{
                                    //Atualize o score de quem matou e de quem morreu
                                    players[(*bullet)->playerId]->kills++;
                                    players[(*bullet)->playerId]->killStreak++;
                                    
                                    //Checa se chegou ao score máximo
                                    if (players[(*bullet)->playerId]->kills >= MAX_SCORE)
                                        maxScoreReached = true;
                                    
                                    if ((players[(*bullet)->playerId]->killStreak == 1 && firstBlood == false) || players[(*bullet)->playerId]->killStreak > 1){
                                        firstBlood = true;
                                        
                                        //Enviar mensagem de kill streak
                                        SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.KILL_OCCURRED, 1, (*bullet)->playerId, players[(*bullet)->playerId]->killStreak);
                                        sendDataToAllConnectedSockets();
                                    }
                                    
                                    player->second->death(SDL_GetTicks());
									//Enviar mensagem dizendo que alguem matou alguem
									SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.KILL_OCCURRED, 0, (*bullet)->playerId, player->second->id);
                                    sendDataToAllConnectedSockets();
								}
								else
								{
                                    //player damaged, update this infor to all players
									SPRINTF(buffer, "%d %d %d \n", MESSAGE_TYPE.PLAYER_HP, player->second->id, player->second->currentHP);
                                    sendDataToAllConnectedSockets();
								}

                                
                            }
                        }
                        
                        //move to the next player
                        ++player;
                    }
                    
                    if ((*bullet)->destroy) {
                        
                        //manda mensagem de destruir bala para todos os clientes
                        SPRINTF(buffer, "%d %d %d \n", MESSAGE_TYPE.REMOVE_BULLET, (*bullet)->type, (*bullet)->bulletId);
                        sendDataToAllConnectedSockets();
                        
                        delete * bullet;
                        bullet = bullets.erase(bullet);
                    }else{
                        //update bullet position
                        SPRINTF(buffer, "%d %d %d %d %d \n", MESSAGE_TYPE.BULLETS, (*bullet)->x, (*bullet)->y, (*bullet)->type, (*bullet)->bulletId);
                        sendDataToAllConnectedSockets();
                        //move to the next bullet
                        ++bullet;
                    }
                }
                
                
                buffer[0] = '\0';
                startTimeNetwork = SDL_GetTicks();
            }

//==========================================================================Verifica por requisições enviadas pelos clientes
			
        while (SDLNet_CheckSockets(socketSet, 0)){
				for (std::map<int, Player*>::iterator player = players.begin(); player != players.end(); ++player){
					
                    if (SDLNet_SocketReady(player->second->socket)){
                        //Atualiza o último pacote recebido pelo servidor do cliente em questão
						player->second->socketTimeout = SDL_GetTicks();

						if (SDLNet_TCP_Recv(player->second->socket, &size, sizeof(int))){
							int readBytes;
							readBytes = SDLNet_TCP_Recv(player->second->socket, buffer, size);

							if (readBytes != size){
								printf("\n Warning Cannot read the correct size of data from socket %d, some information can be corrupted!", player->second->id);
								printf("\n Skipping the iteration!");
								continue;
							}
						}
						else
							continue;

						int messageType;
						SSCANF(buffer, "%d", &messageType);

                        //Movement message received
						if (messageType == MESSAGE_TYPE.SEND_PLAYER_POSITION)
						{
                            //Update the player position
                            int id, x, y;
                            SSCANF(buffer, "%d %d %d %d", &messageType, &id, &x, &y);
                            player->second->setPosition(x, y);
                            
                            //Sends exaclty the same received message
                            sendDataToAllConnectedSocketsExceptOne(player->second->id);
                            
                            //colision check with list of items;
                            for (std::map<int,Item*>::iterator item=items.begin(); item!=items.end();){
                                //If player collided with a item
                                if (Collidable::checkCollision(player->second->collisionRect, item->second->colisionRect)){
                                    //item treatment
                                    switch (item->second->type) {
                                        case 0: //new weapon
                                            player->second->bulletType = item->second->iInfo;
                                            break;
                                        case 1: //ammo
                                            //server does not know aboyt player ammo
                                            break;
                                        case 2: //first aid kit
                                            player->second->currentHP += item->second->iInfo;
                                            
                                            if (player->second->currentHP > player->second->maxHP)
                                                player->second->currentHP = player->second->maxHP;
                                            
                                            //update hp info to all other players
                                            SPRINTF(buffer, "%d %d %d \n", MESSAGE_TYPE.PLAYER_HP, player->second->id, player->second->currentHP);
                                            sendDataToAllConnectedSocketsExceptOne(player->second->id);
                                            break;
                                        default:
                                            break;
                                    }
                                    
                                    //send item picked to all players
                                    SPRINTF(buffer, "%d %d %d \n", MESSAGE_TYPE.ITEM_PICKED_UP, player->second->id, item->second->id);
                                    sendDataToAllConnectedSockets();
                                    
                                    items.erase(item++);
                                }else{
                                    ++item;
                                }
                            }
						}
						else if (messageType == MESSAGE_TYPE.PLAYER_DISCONECTED){
							//Comando que aciona a remoção do cliente do servidor
                            //informa aos outros clientes que o mesmo saiu
                            sendDataToAllConnectedSocketsExceptOne(player->second->id);

							//Remove o client do servidor
							SDLNet_TCP_DelSocket(socketSet, player->second->socket);
							SDLNet_TCP_Close(player->second->socket);
                            
                            players.erase(player++);
                            
							numberOfPlayers--;
							std::cout << "\n Player ID:" << player->second->id << " Disconnected!";
							std::cout << "\n Total Players Connected: " << numberOfPlayers;
                            
                            break;
						}
						else if (messageType == MESSAGE_TYPE.SEND_BULLET){
							//Manda a mensagem da bala recebida para todos os outros clients, menos para ele mesmo
                            int messageType, x, y, angle, playerID, bulletType;
                            SSCANF(buffer, "%d %d %d %d %d %d \n", &messageType, &x, &y, &angle, &playerID, &bulletType);
                            Bullet* bullet = new Bullet(x, y, angle, player->second->id, bulletType, bulletID);
                            bullet->deltaTime = SDL_GetTicks();
                            bullet->setPosition(cos(( bullet->angle-180) *( PI/180 ) ) * 50, sin( (bullet->angle-180) *( PI/180 ) ) * 50);
                            
                            bulletID++;
                            bullets.push_back(bullet);
						}
						else if (messageType == MESSAGE_TYPE.NICKNAME)
						{
							char nickBuffer[100];
							
                            //coppy byte by byte into char nickname
							int x = 2;
							for (int l = 0; l <= 102; l++)
							{
								nickBuffer[l] = buffer[x];
								if (buffer[x] == '\n')
								{
									nickBuffer[l] = '\0';
									break;
								}
								x++;
							}
                            
                            std::map<int, Player*>::iterator temp;
                            temp = players.find(player->second->id);
                            
                            if (temp != players.end()){
                                printf("\nPlayer found, name setted on the server");
                            
                                STRCPY(player->second->nickname, nickBuffer);
                                 
                                //New connection, send the actual id (i) and his nickname to the others
                                SPRINTF(buffer, "%d %d %s \n", MESSAGE_TYPE.NICKNAME, player->second->id, nickBuffer);

                                //Send the nickname to the others players
                                sendDataToAllConnectedSocketsExceptOne(player->second->id);
                            }else
                                printf("\nPlayer not found, error setting his name on server");
						}
						else if (messageType == MESSAGE_TYPE.REQUEST_PLAYER_NAME)
						{
							int messageType, id;
							SSCANF(buffer, "%d %d \n", &messageType, &id);

							//Send the nickname to the player who requested
							SPRINTF(buffer, "%d %d %s \n", MESSAGE_TYPE.NICKNAME, id, players[id]->nickname);
                            sendData(player->second->socket);
						}
						else if (messageType == MESSAGE_TYPE.REQUEST_SCORE)
						{
                            
                            for (std::map<int,Player*>::iterator p=players.begin(); p!=players.end(); ++p){
                                //Envia o id do player, e seus valores de kills e deaths para o player que requisitou
                                SPRINTF(buffer, "%d %d %d %d \n", MESSAGE_TYPE.PLAYER_SCORE, p->second->id, p->second->kills, p->second->deaths);

                                //Envia sempre para o socket (i) que requisitou o score
                                sendData(player->second->socket);
							}
						}
					}
                    //verifica quanto tempo o socket está sem responder
                    else if (SDL_GetTicks() - player->second->socketTimeout > 50000){
                        std::cout << "TIME OUT! : " << player->second->id;
                        SPRINTF(buffer, "%d %d \n", MESSAGE_TYPE.PLAYER_DISCONECTED, player->second->id);
                        //remover o jogador, pois o timeout excedeu
                        sendDataToAllConnectedSocketsExceptOne(player->second->id);
                        
                        //Remove o client do servidor
                        SDLNet_TCP_DelSocket(socketSet, player->second->socket);
                        SDLNet_TCP_Close(player->second->socket);
                        
                        //remove player from memmory
                        players.erase(player++);
                        
                        numberOfPlayers--;
                    }
				}
            
		}
	}

	//Deleta todos os players ainda conectados e desliga o servidor
	for (std::map<int,Player*>::iterator player=players.begin(); player!=players.end(); ++player)
        SDLNet_TCP_Close(player->second->socket);

	//Finaliza as conexıes criadas
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_TCP_Close(server);
	SDLNet_Quit();
	SDL_Quit();

	std::cout << "Server Stopped!";
	return 0;
};

//generate a new item in a random position
void generateNewItem(int* type, int* posX, int* posY, int* iInfo){
    *type = rand() % 3;
    
    switch (*type) {
        case 0://New random weapon
            *iInfo = rand() % 5;
            break;
        case 1://ammo
            *iInfo = 30;
            break;
        case 2://health
            *iInfo = 40;
            break;
        default:
            break;
    }
    
    generateRandomPosition(posX, posY);
}

void generateRandomPosition(int* posX, int* posY){
    bool collision = true;
    while (collision) {
        /* initialize random seed: */
        
        *posX = rand() % ((mMap->sizeX * TILE_WIDTH) - TILE_WIDTH);
        *posY = rand() % ((mMap->sizeY * TILE_HEIGHT) - TILE_HEIGHT);
        
        Agent player = Agent(*posX, *posY, 96, 96, 1);
        
        collision = checkMapCollision(*posX, *posY, player.colisionRect);
    }
}


//Check collision with the map, with the current SDL_Rect passed as parameter
bool checkMapCollision(int x, int y, SDL_Rect objectCollisionRect){
    Agent object = Agent(objectCollisionRect.x, objectCollisionRect.y, objectCollisionRect.w, objectCollisionRect.h, 1);
    
    for (int x = 0; x < mMap->sizeX; x++) {
        for (int y = 0; y < mMap->sizeY; y++) {
            if (mMap->layer[1]->layer[x][y] != 0) {
                if (Collidable::checkCollision(Agent(x*TILE_WIDTH, y*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, 1).colisionRect, object.colisionRect))
                    return true;
            }
        }
    }
    
    return false;
}



void sendData(TCPsocket socket){
    int size = (strlen(buffer) + 1);
    SDLNet_TCP_Send(socket, &size, sizeof(int));
    SDLNet_TCP_Send(socket, buffer, size);
}

void sendDataToAllConnectedSockets(){
    for (std::map<int, Player*>::iterator it = players.begin(); it != players.end(); ++it)
        sendData(it->second->socket);
}

void sendDataToAllConnectedSocketsExceptOne(int id){
    for (std::map<int, Player*>::iterator it = players.begin(); it != players.end(); ++it)
        if (it->second->id != id)
            sendData(it->second->socket);
}
