#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>


#include </home/nikita/inf_proj/cell_1.cpp>


std::vector< std::pair<int, int> > Read(std::string filename){
        std::vector< std::pair<int, int> > base;
	std::string line;

       	std::ifstream in(filename); // окрываем файл для чтения
        int i_line = 0;
        if (in.is_open()){
                while (getline(in, line)){
                        for(int j_col = 0; j_col < line.size(); j_col++){
                                if(line[j_col] == 'O') { //Большая О(как оборона), не ноль
                                        base.push_back({i_line, j_col});
                                }
                        }
                        i_line++;
                }

        }
        in.close(); // закрываем файл
	return base;
}

int main()
{
	int window_length = 1500;
	int window_height = 1500;
	int cell_size = 10;
	sf::RenderWindow window(sf::VideoMode(window_length, window_height), "SFML works!");
	Field f(window_length / cell_size, window_height / cell_size, cell_size);


	std::vector< std::pair<int, int> > base1 = Read("database/in/1.txt");
	//std::vector< std::pair<int, int> > base2 = Read("database/in/2.txt");

	f.Set_Position(base1, 25, 25);
	//f.Set_Position(base2, 75, 75);


	bool Ispause = 1;
    	bool Isspace = 0;
	while (window.isOpen())
	{
		sf::Event event;
        	while (window.pollEvent(event))
        	{
            		if (event.type == sf::Event::Closed)
               			window.close();
        	}


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                sf::sleep(sf::milliseconds(10));
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                f.Print(window);

                sf::sleep(sf::milliseconds(100));
            }


            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i localPos = sf::Mouse::getPosition(window);
                sf::sleep(sf::milliseconds(00));
                int ii = localPos.x / cell_size;
                int jj = localPos.y / cell_size;
		if (!(ii <= 0 || jj <= 0 || ii >= (window_height / cell_size - 1) || jj >= (window_length / cell_size - 1))) 
                if(f.grind[ii][jj].is_alive == 0){
                    f.grind[ii][jj].is_alive = true;
                    //f.grind[ii][jj].Print(ii, jj, 1, cell_size, window);
                    f.Print(window);

                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                sf::Vector2i localPos = sf::Mouse::getPosition(window);
                sf::sleep(sf::milliseconds(100));
                int ii = localPos.x / cell_size;
                int jj = localPos.y / cell_size;

                if(f.grind[ii][jj].is_alive){
                        sf::sleep(sf::milliseconds(10));
                    f.grind[ii][jj].is_alive = false;
                    f.grind[ii][jj].Print(ii, jj, 0, cell_size, window);
                    //f.Print(window);

                }
            }
	    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                std::ofstream out("database/out/1.txt"); // окрываем файл для чтения
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

            //f.Print(window);
            f.Recount();
            f.Print(window);

        }

        //sf::sleep(sf::milliseconds(100));



    }

    return 0;
}
