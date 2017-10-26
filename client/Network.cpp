//
//  Network.h
//  game-project
//
//  Created by Diogo Falcao on 06/10/14.
//  Copyright (c) 2014 dfdf. All rights reserved.
//

#include "Network.h"

#if defined(__APPLE__)
    #define SSCANF sscanf
    #define SPRINTF sprintf
#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
    #define SSCANF sscanf_s
    #define SPRINTF sprintf_s
#endif

#include "Global.h"
int c = 0;

const struct{
    //SERVER COMMANDS
    int NEW_PLAYER = 0;
    int PLAYER_POSITION = 1;
    int PLAYER_DISCONECTED = 2;
    int BULLETS = 3;
    int PLAYER_HP = 4;
    int KILL_OCCURRED = 5;
    int NICKNAME = 9;
    int PLAYER_SCORE = 11;
    int ITEM_SPAWN = 12;
    int PLAYER_RESPAWN = 13;
    int ITEM_PICKED_UP = 14;
    int REMOVE_BULLET = 15;
    int ROUND_END = 16;
    int ROUND_START = 17;
    
    //CLIENT COMMANDS
    int SEND_PLAYER_POSITION = 21;
    int SEND_BULLET = 23;
    int REQUEST_SCORE = 22;
    int REQUEST_PLAYER_NAME = 24;
} MESSAGE_TYPE;

network::network(const char* ipchar, char* nickName)
{
	tmp[0] = '\0';
	std::cout << "\nConnecting to IP: " << ipchar;

	SDLNet_Init();
	IPaddress ip;
	connected = true;

	//Conecta com o servidor
	if (SDLNet_ResolveHost(&ip, ipchar, 1234) != 0)
	{
		std::cout << "\n Connection Error (Cannot Solve Host)";
		connected = false;
	}

	//Abre uma comunica‹o com o servidor
	connection = SDLNet_TCP_Open(&ip);

	if (connection == NULL)
	{
		std::cout << "\n Connectionn Error (Bad IP)";
		connected = false;
	}

	if (connected)
	{
		server = SDLNet_AllocSocketSet(1);
		SDLNet_TCP_AddSocket(server, connection);
		std::cout << "\n Connection Successful";

		SPRINTF(tmp, "%d %s \n", MESSAGE_TYPE.NICKNAME, nickName);

		int size = (strlen(tmp) + 1);
		SDLNet_TCP_Send(connection, &size, sizeof(int));
		SDLNet_TCP_Send(connection, tmp, size);
		std::cout << "\n Nickname Sent!";
	}
}



network::~network()
{

	SPRINTF(tmp, "%d \n", MESSAGE_TYPE.PLAYER_DISCONECTED);
	int size = (strlen(tmp) + 1);
	SDLNet_TCP_Send(connection, &size, sizeof(int));
	SDLNet_TCP_Send(connection, tmp, size);

	SDLNet_TCP_Close(connection);
	SDLNet_FreeSocketSet(server);
	SDLNet_Quit();
}


void network::send(Player* p)
{
	if (ready)
	{
        SPRINTF(tmp, "%d %d %d %d %d %d \n", MESSAGE_TYPE.SEND_PLAYER_POSITION, p->id, p->mMovement.position.x, p->mMovement.position.y, p->mMovement.lookAngle, 0);

		int size = (strlen(tmp) + 1);
		SDLNet_TCP_Send(connection, &size, sizeof(int));
		SDLNet_TCP_Send(connection, tmp, size);

		tmp[0] = '\0';
	}
}

void network::requestName(int id)
{
	if (ready)
	{
		//10 indica uma requisição de nickname para o id
		SPRINTF(tmp, "%d %d \n", MESSAGE_TYPE.REQUEST_PLAYER_NAME, id);

		int size = (strlen(tmp) + 1);
		SDLNet_TCP_Send(connection, &size, sizeof(int));
		SDLNet_TCP_Send(connection, tmp, size);

		tmp[0] = '\0';
	}
}

void network::requestScore()
{
	if (ready)
	{
		//10 indica uma requisição de atualização de scores
		SPRINTF(tmp, "%d \n", MESSAGE_TYPE.REQUEST_SCORE);

		int size = (strlen(tmp) + 1);
		SDLNet_TCP_Send(connection, &size, sizeof(int));
		SDLNet_TCP_Send(connection, tmp, size);

		tmp[0] = '\0';
	}
}


void network::sendShot(Player* player)
{
	if (ready)
	{
		for (std::vector<Bullet*>::iterator it = player->mWeapon->bullets.begin(); it != player->mWeapon->bullets.end(); it++){
			//x, y, angle, id, type
			SPRINTF(tmp, "%d %d %d %d %d %d \n", MESSAGE_TYPE.SEND_BULLET, (*it)->mMovement.position.x, (*it)->mMovement.position.y, (*it)->info.angle, player->id, player->mWeapon->bulletType);

			int size = (strlen(tmp) + 1);
			SDLNet_TCP_Send(connection, &size, sizeof(int));
			SDLNet_TCP_Send(connection, tmp, size);
		}

		player->mWeapon->bullets.clear();

		tmp[0] = '\0';
	}
}

void network::recv(Player* player, std::map<int, Player*>* enemies, std::map<int, Item*>* itens)
{
	
	while (SDLNet_CheckSockets(server, 0) > 0 && SDLNet_SocketReady(connection))
	{
		int n = 0;
		int aux = SDLNet_TCP_Recv(connection, &n, sizeof(int));

		//Se recebeu algo, e se o valor lido for a quantidade correta
		if (aux > 0)
		{
			int readBytes = 0;
			unsigned short total = 0;
			unsigned short bytesleft = n;

			int teste = 0;
			int time = SDL_GetTicks();
			
			while (total < n)
			{
				if (n > 10000)
					return;

				readBytes = SDLNet_TCP_Recv(connection, &tmp[total], bytesleft);

				if (readBytes == -1) { break; }
				total += readBytes;
				bytesleft -= readBytes;
				
				printf("\n BUFFER: %s", tmp);
				if (teste != 0)
				{
					printf("\n READ: %d, TOTAL: %d", readBytes, n);
					printf("\n Network Package Incomplete, recovering the rest of data...");
					printf("\n BUFFER: %s", tmp);
					
				}


				if (SDL_GetTicks() - time > 10000)
				{
					printf("\n CONNECTION LOST! TIME OUT!");
					return;
				}
				teste++;
			}

			if (teste > 1)
				printf("\n BUFFER 2: %s", tmp);
		}
		else
		{
			printf("\n Cannot read the correct amount of data: %d, N: %d", aux, n);

			//int temp = 0;


			//while(temp < sizeof(int))
			//{
			//	temp += aux;
			//	aux = SDLNet_TCP_Recv(connection, &tmp[temp], sizeof(int) - temp);
			//	if (aux <= 0)
			//		return;

			//	printf("\n ERASING TCP BUFFER %d", n);
			//	printf("\n Buffer: %s", tmp);
			//	tmp[0] = '\0';
			//}
			
			return;
		}
			

		int type, id;
		SSCANF(tmp, "%d %d", &type, &id);
		
		if (type == MESSAGE_TYPE.NEW_PLAYER)
		{
			//Coloque o ID do jogador como sendo o enviado
            int x, y;
			SSCANF(tmp, "%d %d %d %d %d", &type, &id, &currentMap, &x, &y);
			player->id = id;

            printf("\nID RECEIVED %d, Current Map: %d",id, currentMap);
			ready = true;
            
            int sizeX, sizeY;
            if (mMap == NULL) {
                sizeX = 20;
                sizeY = 20;
            }else{
                sizeX = mMap->sizeX;
                sizeY = mMap->sizeY;
            }
            
            player->setPosition(x, y, sizeX, sizeY);
		}
		else if (type == MESSAGE_TYPE.SEND_PLAYER_POSITION)
		{	
			int x, y, angle, npc;
			SSCANF(tmp, "%d %d %d %d %d %d", &type, &id, &x, &y, &angle, &npc);

			if (id < 0 || id > 2000)
			{
				printf("\n Warning Connection Problem Invalid ID Received! %d", id);
				return;
			}

			std::map<int, Player*>::iterator tempEnemie;
			tempEnemie = enemies->find(id);

			//Se nao existir nenhum player com aquele ID, adicione
			if (tempEnemie == enemies->end())
			{

				printf("\n NEW ENEMIE ID: %d, X: %d, Y: %d, NPC: %d", id, x, y, npc);
                enemies->insert(std::make_pair(id, new Player(x, y, 96, 96, playerSprite, 0.33, " ", font, weapon1, dead)));

                tempEnemie = enemies->find(id);
				tempEnemie->second->id = id;
				tempEnemie->second->currentHP = 100;


				//Requisita o nome do novo jogador
				if (npc == 0)
					this->requestName(id);
			}
			else
			{
				//ATUALIZE AQUI AS INFORMAÇÕES DO JOGADOR

				//Se não tiver um nome, peça ao servidor
                if (strcmp(tempEnemie->second->nickName, " ") == 0 && tempEnemie->second->playerType == 0)
				{
                    printf("\nRequesting enemie name id %d", tempEnemie->second->id);
					this->requestName(id);
				}
                
                int sizeX = 20, sizeY = 20;

                if (mMap != NULL) {
                    sizeX = mMap->sizeX;
                    sizeY = mMap->sizeY;
                }
                
                tempEnemie->second->setPosition(x, y, sizeX, sizeY);
				tempEnemie->second->setLookAngle(angle);

				//printf("NICK NAME DO MANOLO: %s", tempEnemie->second->nickName);
			}
			

		}
		else if (type == MESSAGE_TYPE.PLAYER_DISCONECTED)
		{
			//RECEBIDA MENSAGEM DE EXIT DE ALGUM PLAYER
			//	remover o inimigo que saiu da lista
			printf("\n ENEMIE DISCONNECTED: %d",id);
			printf(tmp);

			std::map<int, Player*>::iterator tempEnemie;
			tempEnemie = enemies->find(id);

			if (tempEnemie != enemies->end())
			{
				//Remova do mapa o jogador que se desconectou
				enemies->erase(tempEnemie);
			}

		}
		else if (type == MESSAGE_TYPE.BULLETS)
		{
			//Recebe as balas do servidor
            
            int messageType, x, y, type, id;
            SSCANF(tmp, "%d %d %d %d %d", &messageType, &x, &y, &type, &id);
            WeaponType wType;
            switch (type) {
                case 0:
                    wType = weapon1;
                    break;
                case 1:
                    wType = weapon2;
                    break;
                case 2:
                    wType = weapon3;
                    break;
                case 3:
                    wType = weapon4;
                    break;
                case 4:
                    wType = weapon5;
                    break;
                default:
                    break;
            }
            
            player->mWeapon->bulletReceived(x, y, wType, id);
		}
		else if (type == MESSAGE_TYPE.PLAYER_HP)
		{
			//Atualiza o valor do HP
			int messageType, id, hp;

			SSCANF(tmp, "%d %d %d", &messageType, &id, &hp);

			if (id == player->id)
			{
				printf("\n OLD HP: %d, Your Current HP: %d", player->currentHP, hp);
				player->currentHP = hp;
				
				return;
			}
			else
			{
				std::map<int, Player*>::iterator tempEnemie;
				tempEnemie = enemies->find(id);

				if (tempEnemie != enemies->end())
				{
					//Atualiza o HP do jogador
					printf("\n Enemy HP changed ID: %d, OLD HP: %d, NEW HP: %d", tempEnemie->second->id, tempEnemie->second->currentHP, hp);
					tempEnemie->second->currentHP = hp;
					
				}
			}
		}
		else if (type == MESSAGE_TYPE.KILL_OCCURRED)
		{
			//Aditional game info like kill streaks and simple kills
			//P1 killed P2
			int messageType, messageInfo, p1, p2;

			SSCANF(tmp, "%d %d %d %d", &messageType, &messageInfo, &p1, &p2);

			if (messageInfo == 0)
			{
				//One player killed other
				//P1 KILLED P2

				if (p2 == player->id)
				{
					player->currentHP = 0;
					player->alive = false;
					player->mWeapon = new Weapon(100, 2, weapon1);
					player->deathTime = SDL_GetTicks();

					Mix_PlayChannel(-1, gKill, 0);
                    
                    //If the player was killed by a monster, return, there is no need to display messagens for monster kill
                    std::map<int, Player*>::iterator tempEnemie;
                    tempEnemie = enemies->find(p1);
                    if (tempEnemie != enemies->end())
                    {
                        if (tempEnemie->second->isNPC) {
                            return;
                        }
                    }
				}
				else
				{
					std::map<int, Player*>::iterator tempEnemie;
					tempEnemie = enemies->find(p2);

					if (tempEnemie != enemies->end())
					{
						//Remova do mapa o jogador que morreu
						tempEnemie->second->currentHP = 0;
						tempEnemie->second->alive = false;
						tempEnemie->second->deathTime = SDL_GetTicks();
                        if (tempEnemie->second->isNPC) {
                            enemies->erase(tempEnemie);
                            return;
                        }
                    }else{
                        return;
                    }
				}


				std::string messageBuffer;
				if (p1 == player->id)
				{
					std::map<int, Player*>::iterator tempEnemie;
					tempEnemie = enemies->find(p2);

					if (tempEnemie != enemies->end())
					{
						messageBuffer = std::string(player->nickName) + " killed " + std::string(tempEnemie->second->nickName);
					}

				}
					
				if (p2 == player->id)
				{
					std::map<int, Player*>::iterator tempEnemie;
					tempEnemie = enemies->find(p1);

					if (tempEnemie != enemies->end())
					{
						messageBuffer = std::string(tempEnemie->second->nickName) + " killed " + std::string(player->nickName);
					}
				}
				else
				{

					std::map<int, Player*>::iterator tempEnemie1;
					std::map<int, Player*>::iterator tempEnemie2;
					tempEnemie1 = enemies->find(p1);
					tempEnemie2 = enemies->find(p1);

					if (tempEnemie1 != enemies->end() && tempEnemie2 != enemies->end())
					{
						messageBuffer = std::string(tempEnemie1->second->nickName) + " killed " + std::string(tempEnemie2->second->nickName);
					}
				}
					
				

				messages.push_back(messageBuffer);

			}
			else if (messageInfo == 1)
			{
				//Kill Streak

				//P1 is on a kill streak, type: p2

				std::string messageBuffer;
				if (p1 == player->id)
					messageBuffer = std::string(player->nickName) + " just got a";
				else
				{
					std::map<int, Player*>::iterator tempEnemie;
					tempEnemie = enemies->find(p1);

					if (tempEnemie != enemies->end())
					{
						messageBuffer = std::string(tempEnemie->second->nickName) + " just go a";
					}

				}
					

				if (p2 == 1)
				{
					messageBuffer += " first blood!";
					Mix_PlayChannel(-1, gFirstBlood, 0);
				}
				else if (p2 == 2)
				{
					messageBuffer += " double kill!";
					Mix_PlayChannel(-1, gDoubleKill, 0);
				}
				else if (p2 == 3)
				{
					messageBuffer += " triple kill!";
					Mix_PlayChannel(-1, gTripleKill, 0);
				}
				else if (p2 == 4)
				{
					messageBuffer += " ultra kill!";
					Mix_PlayChannel(-1, gUltraKill, 0);
				}
				else if (p2 > 4)
				{
					messageBuffer += " god like!";
					Mix_PlayChannel(-1, gGodLike, 0);
				}
					
				

				messages.push_back(messageBuffer);
			}
			else
				printf("\n Warning! Unknown player info received");


		}
		else if (type == MESSAGE_TYPE.NICKNAME)
		{
			//NickName
			int messageType, id;
			SSCANF(tmp, "%d %d", &messageType, &id);

			char nickBuffer[50];
			int x = 4;
			for (int l = 0; l <= 52; l++)
			{
				nickBuffer[l] = tmp[x];
				if (tmp[x] == '\n')
				{
					nickBuffer[l] = '\0';
					break;
				}
				x++;
			}

			std::map<int, Player*>::iterator tempEnemie;
			tempEnemie = enemies->find(id);
            
            if (tempEnemie->second->isNPC)
                return;

			if (tempEnemie != enemies->end())
			{
				//Adicione o novo nickname no jogador
				strcpy(tempEnemie->second->nickName, nickBuffer);
				printf("\n Enemy id: %d, Nickname: %s, Copiado: %s", id, nickBuffer, tempEnemie->second->nickName);
			}
			else
				printf("\n Cannot add nickname, player dont exist!");
        }
		else if (type == MESSAGE_TYPE.PLAYER_SCORE)
		{
			//MODIFICAÇÃO DE SCORE

			int messageType, id, kill, death;
			SSCANF(tmp, "%d %d %d %d", &messageType, &id, &kill, &death);

			if (id == player->id)
			{
				player->kills = kill;
				player->deaths = death;
				return;
			}
			else
			{
				std::map<int, Player*>::iterator tempEnemie;
				tempEnemie = enemies->find(id);

				if (tempEnemie != enemies->end())
				{
					//Remova do mapa o jogador que morreu
					tempEnemie->second->kills = kill;
					tempEnemie->second->deaths = death;
				}
			}
		}
		else if (type == MESSAGE_TYPE.ITEM_SPAWN)
		{
			//ITEM
			/*
			TIPOMESSAGE TIPOITEM ID POSX POSY INFO


				WEAPON->TIPOARMA
				AMMO->QTDBALA
				LIFE->QTDCURA
			*/
			SDL_Surface* bufferSurface;
			int messageType, itemType, itemId, iPosx, iPosy, iInfo;
			SSCANF(tmp, "%d %d %d %d %d %d", &messageType, &itemType, &itemId, &iPosx, &iPosy, &iInfo);

			if (itemType == 0)
			{
				//Weapon
				itens->insert(std::make_pair(itemId, new Item(itemId, iPosx, iPosy, 96, 96, weaponBox, 1, itemType, iInfo)));
			}
			else if (itemType == 1)
			{
				//Ammo
				itens->insert(std::make_pair(itemId, new Item(itemId, iPosx, iPosy, 96, 96, ammo, 1, itemType, iInfo)));
			}
			else if (itemType == 2)
			{
				//Life
				itens->insert(std::make_pair(itemId, new Item(itemId, iPosx, iPosy, 96, 96, health, 1, itemType, iInfo)));
			}
			else
				printf("\n Item cannot be identified");



		}
        else if (type == MESSAGE_TYPE.PLAYER_RESPAWN)
        {
            //Respawn
            int messageType, id, x, y;
            
            SSCANF(tmp, "%d %d %d %d", &messageType, &id, &x, &y);
            
            if (id == player->id)
            {
                player->currentHP = 100;
                player->alive = true;
                player->setPosition(x, y, mMap->sizeX, mMap->sizeY);
                // TO DO atualizar para arma default
                return;
            }
            else
            {
                std::map<int, Player*>::iterator tempEnemie;
                tempEnemie = enemies->find(id);
                
                if (tempEnemie != enemies->end())
                {
                    //Remova do mapa o jogador que morreu
                    tempEnemie->second->currentHP = 100;
                    tempEnemie->second->alive = true;
                    tempEnemie->second->setPosition(x, y, mMap->sizeX, mMap->sizeY);
                }
            }
        }
		else if (type == MESSAGE_TYPE.ITEM_PICKED_UP)
		{
			int messageType, playerId, itemId;
			SSCANF(tmp, "%d %d %d ", &messageType, &playerId, &itemId);

			std::map<int, Item*>::iterator tempItem;
			tempItem = itens->find(itemId);

			if (tempItem != itens->end())
			{
				//Se eu recebi um item
				if (playerId == player->id)
				{
					if (tempItem->second->type == 0)
					{
						//Weapon

						WeaponType weaponAux;
						if (tempItem->second->info == 0)
							weaponAux = weapon1;
						else if (tempItem->second->info == 1)
							weaponAux = weapon2;
						else if (tempItem->second->info == 2)
							weaponAux = weapon3;
						else if (tempItem->second->info == 3)
							weaponAux = weapon4;
						else if (tempItem->second->info == 4)
							weaponAux = weapon5;

						//Weapon::Weapon(int maxAmmo, int fireRate, WeaponType weapon){
						player->mWeapon = new Weapon(100, 2, weaponAux);
                        Mix_PlayChannel(-1, gGunPickUp, 0);
					}
					else if (tempItem->second->type == 1)
					{
						//Ammo
						Mix_PlayChannel(-1, gWeaponPick, 0);
						player->mWeapon->Reload(tempItem->second->info);
					}
					else if (tempItem->second->type == 2)
					{
						//Life
						Mix_PlayChannel(-1, gHeal, 0);
						player->Heal(tempItem->second->info);
					}

					itens->erase(tempItem);
				}
				else
				{
					//Nao recebi o item, remova do mapa o item
					itens->erase(tempItem);
				}

			}
			else
				printf("\m Item ID not found!");

		}
		else if (type == MESSAGE_TYPE.REMOVE_BULLET)
		{
			//remover bala do mapa de balas
			int messageType, btype, bulletID;
			SSCANF(tmp, "%d %d %d ", &messageType, &btype, &bulletID);

			mPlayer->mWeapon->removeBullet(bulletID);
		}
		else if (type == MESSAGE_TYPE.ROUND_END)
		{
			//Fim de round
			int messageType;
			SSCANF(tmp, "%d", &messageType);
            timerNextRound = SDL_GetTicks();
			endGame = true;
		}
		else if (type == MESSAGE_TYPE.ROUND_START)
		{
			//Inicio de round
			int messageType, x, y;
			SSCANF(tmp, "%d %d", &messageType, &currentMap, &x, &y);

			printf("\n New Current Map: %d", currentMap);

			mPlayer->mWeapon->bulletMap.clear();
			itens->clear();

			mMap->~Map();
			mMap = new Map(maps[currentMap], TILE_WIDTH, TILE_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

			player->setPosition(x, y,mMap->sizeX,mMap->sizeY);

			player->mWeapon = new Weapon(100, 2, weapon1);

			endGame = false;
		}
	}
    tmp[0] = '/0';
}
