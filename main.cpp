#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>


#include </home/nikita/life_proj/cell_1.cpp>


std::vector< std::pair<int, int> > Read(std::string filename){ //функция чтения из файла
        std::vector< std::pair<int, int> > base;
	std::string line;
	std::ifstream in(filename); // окрываем файл для чтения
        int i_line = 0;
        if (in.is_open()){
                while (getline(in, line)){
                        for(int j_col = 0; j_col < line.size(); j_col ++){
                                if(line[j_col] == 'O') { //Большая О(буква), не ноль
                                        base.push_back({i_line, j_col});
                                }
                        }
                        i_line ++;
                }

        }
        in.close(); // закрываем файл
	return base;
}

int main()
{
	std::string filename_out = "database/out/1.txt";
	int window_length = 1500;
	int window_height = 1500;
	int cell_size = 10;
	sf::RenderWindow window(sf::VideoMode(window_length, window_height), "That's how Life works");

	Field f(window_length / cell_size, window_height / cell_size, cell_size); //создаем поле

	std::vector< std::pair<int, int> > base1 = Read("database/in/1.txt"); //считываем начальную расстановку
	//std::vector< std::pair<int, int> > base2 = Read("database/in/2.txt"); 

	f.Set_Position(base1, 25, 25); //ставим
	//f.Set_Position(base2, 75, 75);

	while (window.isOpen())
	{
		sf::Event event;
        	while (window.pollEvent(event))
        	{
            		if (event.type == sf::Event::Closed)
               			window.close();
        	}


        	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //пауза на пробеле
                	sf::sleep(sf::milliseconds(10));
            		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                		f.Print(window);
				sf::sleep(sf::milliseconds(100));
			}
		

            		else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ //рисование лкм
                		sf::Vector2i localPos = sf::Mouse::getPosition(window);
				sf::sleep(sf::milliseconds(10));
				int loc_i = localPos.x / cell_size;
                        	int loc_j = localPos.y / cell_size;
                		if(f.grind[loc_i][loc_j].is_alive == 0){
                    			f.grind[loc_i][loc_j].is_alive = true;
                    			f.Print(window);
				}
            		}
		
            		else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){ //убираем пкм
                		sf::Vector2i localPos = sf::Mouse::getPosition(window);
                		sf::sleep(sf::milliseconds(10));
                		int loc_i = localPos.x / cell_size;
                		int loc_j = localPos.y / cell_size;
				if(f.grind[loc_i][loc_j].is_alive){
                        		sf::sleep(sf::milliseconds(10));
                    			f.grind[loc_i][loc_j].is_alive = false;
                    			f.grind[loc_i][loc_j].Print(loc_i, loc_j, 0, cell_size, window);
                		}
            		}

			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ //двигаем стрелками
                                f.Dvizenie(0, 1);
				sf::sleep(sf::milliseconds(10));
				window.clear(sf::Color::White);
				f.Print(window);
                        }

			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ //двигаем стрелками
                                f.Dvizenie(0, f.n - 1);
                                sf::sleep(sf::milliseconds(10));
                                window.clear(sf::Color::White);
                                f.Print(window);
                        }

			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ //двигаем стрелками
                                f.Dvizenie(1, 0);
                                sf::sleep(sf::milliseconds(10));
                                window.clear(sf::Color::White);
                                f.Print(window);
                        }
			
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ //двигаем стрелками
                                f.Dvizenie(f.m - 1, 0);
                                sf::sleep(sf::milliseconds(10));
                                window.clear(sf::Color::White);
                                f.Print(window);
                        }

	    		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){ //сохранение на C
                		std::ofstream out(filename_out); // окрываем файл для чтения
       				sf::sleep(sf::milliseconds(100));
 				if (out.is_open()){
                			for (int i = 0; i < window_length / cell_size; i ++){
						for (int j = 0; j < window_height / cell_size; j ++){
							if (f.grind[i][j].is_alive) out << 'O';
							else out << '.';
						}
						out << std::endl;
					}
				}
        			out.close(); // закрываем файл
			}
		}
        else{
        	window.clear(sf::Color::White);
            	sf::sleep(sf::milliseconds(100));
            	f.Recount();
            	f.Print(window);
	}
    }

    return 0;
}
