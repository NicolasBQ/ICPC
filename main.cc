#include <iostream>

struct Tile_Node {
    int price;
    int height;
    int index;
    Tile_Node* next;
};

Tile_Node* header_back = NULL;
Tile_Node* header_front = NULL;
Tile_Node* result_back = NULL;
Tile_Node* result_front = NULL;


void get_data(Tile_Node* &header, int n, std::string row) {
    for(int i = 0; i < n; i++) {
        // PRICE
        Tile_Node* tile = new Tile_Node();
        std::cout << "Ingrese el precio del azulejo numero " << i + 1 << " de la fila " << row << std::endl;
        std::cin >> tile->price;
        
        // HEIGHT
        std::cout << "Ingrese la altura del azulejo numero " << i +1 << " de la fila " << row << std::endl;
        std::cin >> tile->height;

        
        tile->index = i + 1;
        tile->next = header;
        header = tile;
    }
};


void price_sort(Tile_Node* &header)
{
    Tile_Node* p = header;
    Tile_Node* q = p->next;
    Tile_Node* end_pointer = NULL;
    int point_price;
    int point_height;
    int point_index;

    while (p->next != end_pointer)
    {
        while (p->next != end_pointer)
        {
            if (q->price < p->price)
            {
                point_price = p->price;
                p->price = q->price;
                q->price = point_price;

                point_index = p->index;
                p->index = q->index;
                q->index = point_index;

                point_height = p->height;
                p->height = q->height;
                q->height = point_height;
            } else if(q->price == p->price) {
                if(q->height > p->height) {
                    point_price = p->price;
                    p->price = q->price;
                    q->price = point_price;

                    point_index = p->index;
                    p->index = q->index;
                    q->index = point_index;

                    point_height = p->height;
                    p->height = q->height;
                    q->height = point_height;
                }
            }

            p = p->next;
            q = p->next;
        };
        end_pointer = p;
        p = header;
        q = p->next;
    }

    header = p;
};


void height_sort(Tile_Node* &header)
{
    Tile_Node* p = header;
    Tile_Node* q = p->next;
    Tile_Node* end_pointer = NULL;
    int point_price;
    int point_height;
    int point_index;

    while (p->next != end_pointer)
    {
        while (p->next != end_pointer)
        {
            if (q->height > p->height)
            {
                point_height = p->height;
                p->height = q->height;
                q->height = point_height;

                point_index = p->index;
                p->index = q->index;
                q->index = point_index;

                point_price = p->price;
                p->price = q->price;
                q->price = point_price;
            } else if(q->height == p->height) {
                if(q->height < p->height) {
                    point_price = p->price;
                    p->price = q->price;
                    q->price = point_price;

                    point_index = p->index;
                    p->index = q->index;
                    q->index = point_index;

                    point_height = p->height;
                    p->height = q->height;
                    q->height = point_height;
                }
            }

            p = p->next;
            q = p->next;
        };
        end_pointer = p;
        p = header;
        q = p->next;
    }

    header = p;
};

void add_final_element(Tile_Node* &header, Tile_Node* &tile)
{
    Tile_Node* head_node = header;
    Tile_Node* last_node;

    while (head_node != NULL)
    {
        if (head_node->next == NULL)
        {
            last_node = head_node;
        }

        head_node = head_node->next;
    }

    last_node->next = tile;
    tile->next = NULL;
};


int main() {
    int n;
    bool possible = true;
    std::cout << "Ingrese la cantidad de azulejos para cada fila" << std::endl;
    std::cin >> n;

    // GET BACK ROW DATA
    get_data(header_back, n, "trasera");
    get_data(header_front, n, "frontal");

    // ORDER FRONT BY CHEAPEST PRICE
    price_sort(header_front);

    // ORDER BACK BY SMALLEST HEIGHT
    height_sort(header_back);

    // ANSWER
    while(header_back != NULL && header_front != NULL) {
        if(header_back->height > header_front->height) {
            if(header_back->next == NULL || header_back->price <= header_back->next->price) {
                Tile_Node* tile_back = new Tile_Node();
                Tile_Node* tile_front = new Tile_Node();

                tile_back->index = header_back->index;
                tile_back->price = header_back->price;
                tile_back->height = header_back->height;

                
                if(result_back == NULL) {
                    tile_back->next = result_back;
                    result_back = tile_back;
                } else {
                    add_final_element(result_back, tile_back);
                }

                tile_front->index = header_front->index;
                tile_front->price = header_front->price;
                tile_front->height = header_front->height;


                if(result_front == NULL) {
                    tile_front->next = result_front;
                    result_front = tile_front;
                } else {
                    add_final_element(result_front, tile_front);
                }
            } else {
                possible = false;
                break;
            }
        } else {
            possible = false;
            break;
        }

        header_back = header_back->next;
        header_front = header_front->next;
    }


    if(possible) {
        std::cout << "BACK" << std::endl;
        while(result_back != NULL) {
            std::cout << result_back->index << std::endl;
            result_back = result_back->next;
        }



        std::cout << "FRONT" << std::endl;
        while(result_front != NULL) {
            std::cout << result_front->index << std::endl;
            result_front = result_front->next;
        }
    } else {
        std::cout << "Impossible" << std::endl;
    }


    return 0;
} 



