#include <vector>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<queue>

template<typename T>
void Sdvig(T& mas, int delta){
    int n = mas.size();

    delta %= n;
    if(delta == 0) return;

    std::queue<typename T::value_type> first_part;
    for(int i = 0; i < delta; i++){
        first_part.push(std::move(mas[i]));
    }

    for(int i = 0; i <  n - delta; i++){
        mas[i] = std::move(mas[i + delta]);
    }

    for(int i = n - delta; i < n; i++){
        mas[i] = first_part.front();
        first_part.pop();
    }
}

class Cell {
    public:
        bool is_alive;
        int alive_nb;
        Cell(): is_alive(false), alive_nb(0){}

    void Print(int i, int j, bool t, int len, sf::RenderWindow &window){
        sf::RectangleShape rectangle(sf::Vector2f(len, len));
        rectangle.move(i * len, j * len);

        if(t) rectangle.setFillColor(sf::Color::Black);
        else  rectangle.setFillColor(sf::Color::White);

       	window.draw(rectangle);
	window.display();
	}


};

struct Field {

        int length;
        int n, m;

        std::vector <std::vector <Cell> > grind;

        Field(int n_, int m_, int length_): n(n_), m(m_), length(length_){
                grind.resize(n);
                for(int i = 0; i < n; i++) {
                        grind[i].resize(m);
                }
        }

        void Set_Position(std::vector< std::pair<int, int> > base, int sdvigx, int sdvigy){
		for (int k = 0; k < base.size(); k++){
			grind[base[k].first + sdvigx][base[k].second + sdvigx].is_alive = true;
		}
	}

	void Dvizenie(int delta_x, int delta_y){
        	Sdvig(grind, delta_y);
        
       		for(int i = 0; i < n; i++)
            		Sdvig(grind[i], delta_x);
   	}

        void Print(sf::RenderWindow &window) const{
        for (int i = 0; i < n; i++){
                        for (int j = 0; j < m; j++){
                if(grind[i][j].is_alive){
                    sf::RectangleShape rectangle(sf::Vector2f(length, length));
                    rectangle.move(i * length, j * length);

                    rectangle.setFillColor(sf::Color::Black);

                    window.draw(rectangle);
                }
                        }
                }
                window.display();
        }
	void Recount(){
                for (int i = 0; i < n; i++){
            		for (int j = 0; j < m; j++){
                		grind[i][j].alive_nb    = grind[(i - 1 + n) % n][(j - 1 + m) % m].is_alive
				                	+ grind[(i - 1 + n) % n][j].is_alive
						       	+ grind[(i - 1 + n) % n][(j + 1 + m) % m].is_alive
                                      		        + grind[i][(j - 1 + m) % m].is_alive
						       	+ grind[i][(j + 1 + m) % m].is_alive
                                     		        + grind[(i + 1 + n) % n][(j - 1 + m) % m].is_alive
						       	+ grind[(i + 1 + n) % n][j].is_alive
						       	+ grind[(i + 1 + n) % n][(j + 1 + m) % m].is_alive;
                //if(grind[i][j].alive_nb >= 2) std::cout << "YEs: " << i << " " << j << std::endl;
            }
        }
                for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (grind[i][j].is_alive){
                    if (grind[i][j].alive_nb < 2 || grind[i][j].alive_nb > 3)
                        grind[i][j].is_alive = false;
                }
                else{
                    if (grind[i][j].alive_nb == 3)
                        grind[i][j].is_alive = true;

                }
            }
        }

        }
};


                                                                                                                                          //     91,0-1        Bot


