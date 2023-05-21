#include <iostream>
#include <chrono>
#include <thread>
#include "src/include/SDL2/SDL.h"

int WIDTH = 800, HEIGHT = 600;
//Dimensões da janela
//Window dimensions

int delay = 0;
bool programQuit = false;

float sizeMultiplier = 1;
//Toma conta da proporção dos elementos
//Handles the elements’ proportion

struct time_textures{
    SDL_Texture *phrase;
    SDL_Texture *milisec;
    SDL_Texture *sec;
    SDL_Texture *min;
    SDL_Texture *hour;
    SDL_Texture *error;
};
struct info_textures{
    SDL_Texture *size;
    SDL_Texture *quit;
    struct time_textures time;
};
struct name_textures{
    SDL_Texture *bubble;
    SDL_Texture *selection;
    SDL_Texture *insertion;
    SDL_Texture *merge;
    SDL_Texture *quick;
    SDL_Texture *heap;
};
struct size_button_textures{
    SDL_Texture *one;
    SDL_Texture *ten;
    SDL_Texture *hundred;
    SDL_Texture *max;
    SDL_Texture *min;
};
struct delay_button_textures{
    SDL_Texture *on;
    SDL_Texture *off;
    SDL_Texture *temporary;
};
struct button_textures{
    SDL_Texture *next;
    SDL_Texture *previous;
    SDL_Texture *start;
    SDL_Texture *sort;
    SDL_Texture *randomize;
    struct delay_button_textures delay;
    struct size_button_textures up;
    struct size_button_textures down;
};
struct number_textures{
    SDL_Texture *zero;
    SDL_Texture *one;
    SDL_Texture *two;
    SDL_Texture *three;
    SDL_Texture *four;
    SDL_Texture *five;
    SDL_Texture *six;
    SDL_Texture *seven;
    SDL_Texture *eight;
    SDL_Texture *nine;
};
struct all_textures{
    struct number_textures numbers;
    struct button_textures buttons;
    struct name_textures names;
    struct info_textures info;
    SDL_Texture *credits;
};
typedef struct all_textures programTxtr;

struct bar_color{
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
};
struct bar_info{
    int value;
    SDL_Rect rect;
    SDL_Rect lastRect;
    SDL_Rect replace;
    struct bar_color color;
};
typedef struct bar_info bars;

struct bars_being_compared{
    int cmp1 = -1;
    int cmp2 = -1;
    int cmp3 = -1;
};
typedef struct bars_being_compared cmpBars;

//Carrega as texturas do programa
//Loads the program textures
void load_textures(SDL_Renderer *renderer, programTxtr *textures){
    SDL_Surface *surface = SDL_LoadBMP("./textures/next_button.bmp");
    textures->buttons.next = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/previous_button.bmp");
    textures->buttons.previous = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/start_button.bmp");
    textures->buttons.start = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/delay_button.bmp");
    textures->buttons.delay.off = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/delay_button_selected.bmp");
    textures->buttons.delay.on = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/start_sort_button.bmp");
    textures->buttons.sort = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/randomize_button.bmp");
    textures->buttons.randomize = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./textures/sizeText.bmp");
    textures->info.size = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/esc_info.bmp");
    textures->info.quit = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/executado_info.bmp");
    textures->info.time.phrase = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/milisec_info.bmp");
    textures->info.time.milisec = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/sec_info.bmp");
    textures->info.time.sec = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/min_info.bmp");
    textures->info.time.min = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/hour_info.bmp");
    textures->info.time.hour = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/error_info.bmp");
    textures->info.time.error = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./textures/up100_button.bmp");
    textures->buttons.up.hundred = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/up10_button.bmp");
    textures->buttons.up.ten = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/up1_button.bmp");
    textures->buttons.up.one = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/max_button.bmp");
    textures->buttons.up.max = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./textures/down100_button.bmp");
    textures->buttons.down.hundred = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/down10_button.bmp");
    textures->buttons.down.ten = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/down1_button.bmp");
    textures->buttons.down.one = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/min_button.bmp");
    textures->buttons.down.min = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./textures/insertion_sort_button.bmp");
    textures->names.insertion = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/bubble_sort_button.bmp");
    textures->names.bubble = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/selection_sort_button.bmp");
    textures->names.selection = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/quick_sort_button.bmp");
    textures->names.quick = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/merge_sort_button.bmp");
    textures->names.merge = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/heap_sort_button.bmp");
    textures->names.heap = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./textures/zero.bmp");
    textures->numbers.zero = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/one.bmp");
    textures->numbers.one = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/two.bmp");
    textures->numbers.two = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/three.bmp");
    textures->numbers.three = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/four.bmp");
    textures->numbers.four = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/five.bmp");
    textures->numbers.five = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/six.bmp");
    textures->numbers.six = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/seven.bmp");
    textures->numbers.seven = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/eight.bmp");
    textures->numbers.eight = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("./textures/nine.bmp");
    textures->numbers.nine = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./textures/credits.bmp");
    textures->credits = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
//Pega o tempo passado após 01/01/1970 em milisegundos
//Gets the time passed since 01/01/1970 in miliseconds
uint64_t getTime(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


//Printa as informações do vetor
//Prints the array's info
void printInfo(bars vec[], int vecSize){
    std::cout << "v[ ";
    for(int i = 0; i < vecSize; i++){
        if(vec[i].value < 0){
            std::cout << "\033[31m";
        }
        std::cout << "\t"  << vec[i].value << "\033[0m";
    }
    std::cout << "]\n";
    std::cout << "w[ ";
    for(int i = 0; i < vecSize; i++){
        if(vec[i].rect.w < 1){
            std::cout << "\033[31m";
        }
        std::cout << "\t"  << vec[i].rect.w << "\033[0m";
    }
    std::cout << "]\n";
    std::cout << "h[ ";
    for(int i = 0; i < vecSize; i++){
        if(vec[i].rect.h < 1){
            std::cout << "\033[31m";
        }
        std::cout << "\t"  << vec[i].rect.h << "\033[0m";
    }
    std::cout << "]\n";
    std::cout << "x[ ";
    for(int i = 0; i < vecSize; i++){
        if(vec[i].rect.x < 1){
            std::cout << "\033[31m";
        }
        std::cout << "\t"  << vec[i].rect.x << "\033[0m";
    }
    std::cout << "]\n";
    std::cout << "y[ ";
    for(int i = 0; i < vecSize; i++){
        if(vec[i].rect.y < 1){
            std::cout << "\033[31m";
        }
        std::cout << "\t" << vec[i].rect.y << "\033[0m";
    }
    std::cout << "]\n\n\n";
}

//Calcula e posiciona cada barra
//Calculates and positions each bar
void setUpBars(bars vec[], int vecSize){
    float spacing = 25;
    float totalWidth = WIDTH - spacing * 2;
    float barWidth = totalWidth/vecSize;
    float gap = barWidth * 0.2;
    barWidth -= gap * sizeMultiplier;
    for(int i = 0; i < vecSize; i++){
        vec[i].rect.w = barWidth;
        if(vec[i].rect.w == 0){
            vec[i].rect.w = 1;
        }
        vec[i].rect.h = ((HEIGHT * 0.75/vecSize) * vec[i].value) + 1;
        vec[i].rect.x = spacing + (barWidth + gap * sizeMultiplier) * i;
        vec[i].rect.y = HEIGHT - vec[i].rect.h - spacing;
        vec[i].lastRect = vec[i].rect;
        vec[i].replace = vec[i].rect;
    }
    int maxHeightIndex = 0;
    for(int i = 0; i < vecSize; i++){
        if(vec[i].rect.h > vec[maxHeightIndex].rect.h){
            maxHeightIndex = i;
        }
    }
    for(int i = 0; i < vecSize; i++){
        vec[i].replace.h = vec[maxHeightIndex].rect.h;
        vec[i].replace.y = vec[maxHeightIndex].rect.y;
    }
}

//Checa se a barra não é branca
//Checks if the bar is not white
bool checkColorChange(bars *bar){
    if(bar->color.r != 255){
        return true;
    }
    else if(bar->color.g != 255){
        return true;
    }
    else if(bar->color.b != 255){
        return true;
    }
    else{
        return false;
    }
}

//Renderiza as barras
//Renders the bars
void showVec(bars vec[], int vecSize, cmpBars *cmp, SDL_Rect *quit, programTxtr *textures, SDL_Renderer *renderer, bool render, bool complete = false){
    if(cmp != NULL){
        bool renderNewRect = false;

        //Checa se há mais de uma barra por pixel
        //Checks if there is more than one bar per pixel
        if(vec[0].rect.x != vec[1].rect.x){
            for(int i = 0; i < vecSize; i++){
                renderNewRect = false;

                //Checa se o tamanho da barra nessa posição mudou
                //Checks if the bar in this position has changed sizes
                if(vec[i].rect.h != vec[i].lastRect.h){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &vec[i].replace);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    renderNewRect = true;
                    vec[i].lastRect = vec[i].rect;
                }

                if(checkColorChange(&vec[i])){
                    vec[i].color.r = 255;
                    vec[i].color.g = 255;
                    vec[i].color.b = 255;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }

                //Checa se a barra está sendo usada de comparação
                //Checks if the bar is being used for comparisons
                if(i == cmp->cmp1){
                    vec[i].color.r = 255;
                    vec[i].color.g = 0;
                    vec[i].color.b = 0;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }
                else if(i == cmp->cmp2){
                    vec[i].color.r = 0;
                    vec[i].color.g = 0;
                    vec[i].color.b = 255;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }
                else if(i == cmp->cmp3){
                    vec[i].color.r = 0;
                    vec[i].color.g = 255;
                    vec[i].color.b = 0;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }

                //Renderiza a barra caso haja alterações nela
                //Renders the bar if it changed in any aspect
                if(renderNewRect){
                    SDL_RenderFillRect(renderer, &vec[i].rect);
                }   
            }
        }
        else{
            //Quase a mesma lógica, mas como há mais de uma barra por pixel, renderiza somente a maior entre elas
            //Almost the same logic, but because there is more than one bar per pixel, only renders the talles one
            for(int i = 0; i < vecSize; i++){
                renderNewRect = false;
                if(vec[i].rect.h != vec[i].lastRect.h){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &vec[i].replace);
                    vec[i].lastRect = vec[i].rect;
                
                    //Descobre quais barras estão presentes no mesmo pixel que a que mudou
                    //Figures which bars are in the same pixel as the one that changed
                    int start = i;
                    int end = i;
                    while(vec[start].rect.x == vec[i].rect.x && start >= 0){
                        start--;
                    }
                    start++;
                    while(vec[end].rect.x == vec[i].rect.x && end < vecSize){
                        end++;
                    }
                    end--;

                    //Descobre qual é a maior entre elas
                    //Figures wich one is the tallest
                    int maxHeightIndex = start;
                    int j = start;
                    while(j <= end){
                        if(vec[j].rect.h > vec[maxHeightIndex].rect.h){
                            maxHeightIndex = j;
                        }
                        j++;
                    }

                    //Renderiza a barra descoberta pois provavelmente não é a que trocou de cor, e isso ainda será checado
                    //Renders the figured bar beacuse it's probably not the one that has changed colors, and this will still be checked
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &vec[maxHeightIndex].rect);
                }
                if(checkColorChange(&vec[i])){
                    vec[i].color.r = 255;
                    vec[i].color.g = 255;
                    vec[i].color.b = 255;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }
                if(i == cmp->cmp1){
                    vec[i].color.r = 255;
                    vec[i].color.g = 0;
                    vec[i].color.b = 0;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }
                else if(i == cmp->cmp2){
                    vec[i].color.r = 0;
                    vec[i].color.g = 0;
                    vec[i].color.b = 255;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }
                else if(i == cmp->cmp3){
                    vec[i].color.r = 0;
                    vec[i].color.g = 255;
                    vec[i].color.b = 0;
                    SDL_SetRenderDrawColor(renderer, vec[i].color.r, vec[i].color.g, vec[i].color.b, 255);
                    renderNewRect = true;
                }
                if(renderNewRect){
                    SDL_RenderFillRect(renderer, &vec[i].rect);
                }   
            }     
        }
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if(complete){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        for(int i = 0; i < vecSize; i++){
            SDL_RenderDrawRect(renderer, &vec[i].rect);
            SDL_RenderFillRect(renderer, &vec[i].rect);
        }
        SDL_RenderCopy(renderer, textures->info.quit, NULL, quit);    
    }
    if(render){
        SDL_RenderPresent(renderer);
        if(delay != 0){
            SDL_Delay(delay);
        }
    }
}

//Seta o vetor para seu estado organizado
//Sets the array to it's sorted state
void finishSort(bars vec[], int vecSize){
    for(int i = 0; i < vecSize; i++){
        vec[i].value = i + 1;
    }
    setUpBars(vec, vecSize);
}

//Checa se o usuário tentou voltar ao menu ou fechar o programa
//Checks if the user tried going back to the menu or closing the program
bool checkQuit(bars vec[], int vecSize, SDL_Event *event, bool *abort){
    if(SDL_PollEvent(event))
    {
        if(event->type == SDL_KEYDOWN)
        {
            if(SDLK_ESCAPE == event->key.keysym.sym)
            {
                delay = 0;
                *abort = true;
                finishSort(vec, vecSize);
                return true;
            }
        }
        else if(event->type == SDL_QUIT)
        {
            programQuit = true;
            *abort = true;
            return true;
        }   
    }
    if(*abort){
        return true;
    }
    return false;
}

//Completa as barras com a cor verde gradativamente
//Colors the bars green gradually
void showCompleteVec(bars vec[], int vecSize, bool *abort, SDL_Rect *quit, programTxtr *textures, SDL_Renderer *renderer){
    SDL_Event event;
    for(int i = 0; i <= vecSize && !*abort; i++){
        if(checkQuit(vec, vecSize, &event, abort));
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &vec[i].rect);
        SDL_RenderCopy(renderer, textures->info.quit, NULL, quit);
        SDL_RenderPresent(renderer);
    }
}

//Troca os valores e tamanhos das barras
//Swaps values and size of the bars
void swapBars(bars vec[], int i, int j){
    bars aux;
    aux.value = vec[i].value;
    vec[i].value = vec[j].value;
    vec[j].value = aux.value;

    aux.rect.h = vec[i].rect.h;
    vec[i].rect.h = vec[j].rect.h;
    vec[j].rect.h = aux.rect.h;

    aux.rect.y = vec[i].rect.y;
    vec[i].rect.y = vec[j].rect.y;
    vec[j].rect.y = aux.rect.y;
}

//Zera os valores do vetor
//Sets all the array values to zero
void inicialize(bars vec[], int vecSize){
    for(int i = 0; i < vecSize; i++)
    {
        vec[i].value = 0;
        vec[i].rect.w = 0;
        vec[i].rect.h = 0;
        vec[i].rect.x = 0;
        vec[i].rect.y = 0;
    }
}

//Aleatoriza os valores do vetor de acordo com seu tamanho
//Randomizes the array values according to the defined size
void randomize(bars vec[], int vecSize){
    int num;
    bool invec;
    for(int i = 0; i < vecSize; i++)
    {
        do{
            invec = false;
            num = rand() % vecSize + 1;
            for(int j = 0; j < vecSize; j++)
            {
                if(vec[j].value == num)
                {
                    invec = true;
                }
            }
        }while(invec);
        vec[i].value = num;
    }
}

void bubbleSort(bars vec[], int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures){
    cmpBars barsCompared;
    SDL_Event event;
    for(int i = 0; i < vecSize; i++){
        for(int j = i; j < vecSize; j++){
            if(checkQuit(vec, vecSize, &event, abort)){
                return;
            }
            if(vec[i].value > vec[j].value){
                swapBars(vec, i, j);
            }
            barsCompared.cmp1 = i;
            barsCompared.cmp2 = j;
            showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        }
    }
}

void selectionSort(bars vec[], int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures){
    cmpBars barsCompared;
    SDL_Event event;
    int cmp;
    for(int i = 0; i < vecSize - 1; i++){
        cmp = i;
        for(int j = i + 1; j < vecSize; j++){      
            if(checkQuit(vec, vecSize, &event, abort)){
                return;
            }
            if(vec[j].value < vec[cmp].value){
                cmp = j;
            }
            barsCompared.cmp1 = i;
            barsCompared.cmp2 = j;
            barsCompared.cmp3 = cmp;
            showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        }
        swapBars(vec, i, cmp);
    }
}

void insertionSort(bars vec[], int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures){
    cmpBars barsCompared;
    SDL_Event event;
    int j;
    for(int i = 0; i < vecSize - 1; i++){
        j = i + 1;
        barsCompared.cmp1 = i + 1;
        barsCompared.cmp2 = j;
        while(vec[j].value < vec[j - 1].value && j > 0){
            if(checkQuit(vec, vecSize, &event, abort)){
                return;
            }
            swapBars(vec, j, j - 1);
            j--;
            barsCompared.cmp2 = j;
            showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        }
        showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
    }
}

void copyToAux(bars vec[], int x, bars aux[], int y, int vecSize){
    aux[y].value = vec[x].value;
    aux[y].rect.y = vec[x].rect.y;
    aux[y].rect.h = vec[x].rect.h;
}

void copyFromAux(bars vec[], int x, bars aux[], int y, int vecSize){
    vec[x].value = aux[y].value;
    vec[x].rect.y = aux[y].rect.y;
    vec[x].rect.h = aux[y].rect.h;
}

void intercalate(bars vec[], int start, int end, int mid, int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures){
    SDL_Event event;
    cmpBars barsCompared;
    int i, freePos = start, start1 = start, start2 = mid + 1;
    bars aux[vecSize];
    inicialize(aux, vecSize);
    while(start1 <= mid && start2 <= end && !*abort){
        if(checkQuit(vec, vecSize, &event, abort)){
            return;
        }
        if(vec[start1].value > vec[start2].value){
            copyToAux(vec, start2, aux, freePos, vecSize);
            start2++;
            barsCompared.cmp1 = start2;
            barsCompared.cmp2 = start1;
            showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        }
        else{
            copyToAux(vec, start1, aux, freePos, vecSize);
            start1++;
            barsCompared.cmp1 = start2;
            barsCompared.cmp2 = start1;
            showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        }
        freePos++;
    }
    for(i = start1; i <= mid && !*abort; i++){
        if(checkQuit(vec, vecSize, &event, abort)){
            return;
        }
        copyToAux(vec, i, aux, freePos, vecSize);
        freePos++;
        barsCompared.cmp1 = mid;
        barsCompared.cmp2 = i;
        showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
    }
    for(i = start2; i <= end && !*abort; i++){
        if(checkQuit(vec, vecSize, &event, abort)){
            return;
        }
        copyToAux(vec, i, aux, freePos, vecSize);
        freePos++;
        barsCompared.cmp1 = end;
        barsCompared.cmp2 = i;
        showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
    }
    for(i = start; i <= end && !*abort; i++){
        
        if(checkQuit(vec, vecSize, &event, abort)){
            return;
        }
        copyFromAux(vec, i, aux, i, vecSize);
        barsCompared.cmp1 = end;
        barsCompared.cmp2 = i;
        showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
    }
}

void mergeSort(bars vec[], int start, int end, int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures){
    int mid;
    if(!*abort){
        if(start < end){
            mid = (start + end)/2;
            mergeSort(vec, start, mid, vecSize, abort, renderer, quit, textures);
            mergeSort(vec, mid + 1, end, vecSize, abort, renderer, quit, textures);
            intercalate(vec, start, end, mid, vecSize, abort, renderer, quit, textures);
        }
    }
}

void quickSort(bars vec[], int start, int end, int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures){
    SDL_Event event;
    cmpBars barsCompared;
    int i, j, key;
    if((end - start) < 2){
        if(checkQuit(vec, vecSize, &event, abort)){
            return;
        }
        if((end - start == 1)){
            if(vec[start].value > vec[end].value){
                swapBars(vec, start, end);
                barsCompared.cmp1 = start;
                barsCompared.cmp2 = end;
                showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
            }
        }
    }
    else{
        i = start;
        j = end;
        key = vec[start].value;
        barsCompared.cmp1 = i;
        barsCompared.cmp2 = j;
        showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        while(j > i && !*abort){
            
            if(checkQuit(vec, vecSize, &event, abort)){
                return;
            }
            i++;
            barsCompared.cmp1 = i;
            showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
            while(vec[i].value < key && !*abort){
                
                if(checkQuit(vec, vecSize, &event, abort)){
                    return;
                }
                i++;
                barsCompared.cmp1 = i;
                showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
            }
            while(vec[j].value > key && !*abort){
                
                if(checkQuit(vec, vecSize, &event, abort)){
                    return;
                }
                j--;
                barsCompared.cmp2 = j;
                showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
            }
            if(j > i){
                swapBars(vec, i, j);
                barsCompared.cmp1 = i;
                barsCompared.cmp2 = j;
                showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
            }
        }
        swapBars(vec, start, j);
        barsCompared.cmp1 = start;
        barsCompared.cmp2 = j;
        showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        if(!*abort){
            quickSort(vec, start, j - 1, vecSize, abort, renderer, quit, textures);
            quickSort(vec, j + 1, end, vecSize, abort, renderer, quit, textures);    
        }
    }
}

void heapify(bars vec[], int start, int end, int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures, cmpBars *barsCompared){
    SDL_Event event;
    if(checkQuit(vec, vecSize, &event, abort)){
        return;
    }
    int right = 2 * start + 2;
    int left = 2 * start + 1;
    int greater = start;
    barsCompared->cmp1 = left;
    barsCompared->cmp2 = right;
    barsCompared->cmp3 = greater;
    showVec(vec, vecSize, barsCompared, quit, textures, renderer, true);
    if(right <= end && vec[right].value > vec[start].value){
        greater = right;
    }
    if(left <= end && vec[left].value > vec[greater].value){
        greater = left;
    }
    if(greater != start){
        swapBars(vec, start, greater);
        showVec(vec, vecSize, barsCompared, quit, textures, renderer, true);
        if(!*abort){
            heapify(vec, greater, end, vecSize, abort, renderer, quit, textures, barsCompared);    
        }
    }
}

void heapsort(bars vec[], int vecSize, bool *abort, SDL_Renderer *renderer, SDL_Rect *quit, programTxtr *textures){
    SDL_Event event;
    cmpBars barsCompared;
    for(int i = vecSize/2; i >= 0; i--){
        if(checkQuit(vec, vecSize, &event, abort)){
            return;
        }
        heapify(vec, i, vecSize - 1, vecSize, abort, renderer, quit, textures, &barsCompared);
    }
    for(int end = vecSize - 1; end >= 1; end--){
        if(checkQuit(vec, vecSize, &event, abort)){
            return;
        }
        swapBars(vec, 0, end);
        showVec(vec, vecSize, &barsCompared, quit, textures, renderer, true);
        heapify(vec, 0, end - 1, vecSize, abort, renderer, quit, textures, &barsCompared);
    }
}

//Mostra o tamanho atual do vetor
//Displays the current array size
void showSize(int size, SDL_Rect *rect, SDL_Renderer *renderer, programTxtr *textures){
    int aux = size;
    int thousands, hundreds, tens, ones;

    //Obtém cada dígito separadamente do tamanho definido
    //Gets each digit separately from the defined size
    thousands = aux / 1000;
    aux -= thousands * 1000;
    hundreds = aux / 100;
    aux -= hundreds * 100;
    tens = aux / 10;
    aux -= tens * 10;
    ones = aux;

    SDL_Rect numSlot[4];//Cada um dos rects para mostrar os números do tamanho
    for(int i = 0; i < 4; i++){
        numSlot[i].w = 100 * sizeMultiplier;
        numSlot[i].h = 150 * sizeMultiplier;
        numSlot[i].y = (*rect).y;
    }

    //Muda a posiçao dos números dependendo da quantidade de casas decimais
    //Changes the position of the digit slots depending on how many digits there are
    if(size > 999){
        numSlot[0].x = (*rect).x;
        for(int i = 1; i < 4; i++){
            numSlot[i].x = numSlot[i - 1].x + numSlot[0].w;
        }
    }
    else if(size > 99){
        numSlot[2].x = WIDTH/2 - numSlot[0].w/2;
        numSlot[3].x = numSlot[2].x + numSlot[0].w;
        numSlot[1].x = numSlot[2].x - numSlot[0].w;
    }
    else{
        numSlot[3].x = WIDTH/2;
        numSlot[2].x = numSlot[3].x - numSlot[0].w;    
    }
    
    //Checa cada número individualmente e aplica suas respectivas texturas
    //Checks each digit and applies their respective texture
    switch(ones)
    {
        case 0:
        SDL_RenderCopy(renderer, textures->numbers.zero, NULL, &numSlot[3]);
        break;
        case 1:
        SDL_RenderCopy(renderer, textures->numbers.one, NULL, &numSlot[3]);
        break;
        case 2:
        SDL_RenderCopy(renderer, textures->numbers.two, NULL, &numSlot[3]);
        break;
        case 3:
        SDL_RenderCopy(renderer, textures->numbers.three, NULL, &numSlot[3]);
        break;
        case 4:
        SDL_RenderCopy(renderer, textures->numbers.four, NULL, &numSlot[3]);
        break;
        case 5:
        SDL_RenderCopy(renderer, textures->numbers.five, NULL, &numSlot[3]);
        break;
        case 6:
        SDL_RenderCopy(renderer, textures->numbers.six, NULL, &numSlot[3]);
        break;
        case 7:
        SDL_RenderCopy(renderer, textures->numbers.seven, NULL, &numSlot[3]);
        break;
        case 8:
        SDL_RenderCopy(renderer, textures->numbers.eight, NULL, &numSlot[3]);
        break;
        case 9:
        SDL_RenderCopy(renderer, textures->numbers.nine, NULL, &numSlot[3]);
    }
    switch(tens)
    {
        case 0:
        SDL_RenderCopy(renderer, textures->numbers.zero, NULL, &numSlot[2]);
        break;
        case 1:
        SDL_RenderCopy(renderer, textures->numbers.one, NULL, &numSlot[2]);
        break;
        case 2:
        SDL_RenderCopy(renderer, textures->numbers.two, NULL, &numSlot[2]);
        break;
        case 3:
        SDL_RenderCopy(renderer, textures->numbers.three, NULL, &numSlot[2]);
        break;
        case 4:
        SDL_RenderCopy(renderer, textures->numbers.four, NULL, &numSlot[2]);
        break;
        case 5:
        SDL_RenderCopy(renderer, textures->numbers.five, NULL, &numSlot[2]);
        break;
        case 6:
        SDL_RenderCopy(renderer, textures->numbers.six, NULL, &numSlot[2]);
        break;
        case 7:
        SDL_RenderCopy(renderer, textures->numbers.seven, NULL, &numSlot[2]);
        break;
        case 8:
        SDL_RenderCopy(renderer, textures->numbers.eight, NULL, &numSlot[2]);
        break;
        case 9:
        SDL_RenderCopy(renderer, textures->numbers.nine, NULL, &numSlot[2]);
    }
    if(size > 99){
        switch(hundreds)
        {
            case 0:
            SDL_RenderCopy(renderer, textures->numbers.zero, NULL, &numSlot[1]);
            break;
            case 1:
            SDL_RenderCopy(renderer, textures->numbers.one, NULL, &numSlot[1]);
            break;
            case 2:
            SDL_RenderCopy(renderer, textures->numbers.two, NULL, &numSlot[1]);
            break;
            case 3:
            SDL_RenderCopy(renderer, textures->numbers.three, NULL, &numSlot[1]);
            break;
            case 4:
            SDL_RenderCopy(renderer, textures->numbers.four, NULL, &numSlot[1]);
            break;
            case 5:
            SDL_RenderCopy(renderer, textures->numbers.five, NULL, &numSlot[1]);
            break;
            case 6:
            SDL_RenderCopy(renderer, textures->numbers.six, NULL, &numSlot[1]);
            break;
            case 7:
            SDL_RenderCopy(renderer, textures->numbers.seven, NULL, &numSlot[1]);
            break;
            case 8:
            SDL_RenderCopy(renderer, textures->numbers.eight, NULL, &numSlot[1]);
            break;
            case 9:
            SDL_RenderCopy(renderer, textures->numbers.nine, NULL, &numSlot[1]);
        }
    }     
    if(size > 999){
        switch(thousands)
        {
            case 0:
            SDL_RenderCopy(renderer, textures->numbers.zero, NULL, &numSlot[0]);
            break;
            case 1:
            SDL_RenderCopy(renderer, textures->numbers.one, NULL, &numSlot[0]);
            break;
            case 2:
            SDL_RenderCopy(renderer, textures->numbers.two, NULL, &numSlot[0]);
            break;
            case 3:
            SDL_RenderCopy(renderer, textures->numbers.three, NULL, &numSlot[0]);
            break;
            case 4:
            SDL_RenderCopy(renderer, textures->numbers.four, NULL, &numSlot[0]);
            break;
            case 5:
            SDL_RenderCopy(renderer, textures->numbers.five, NULL, &numSlot[0]);
            break;
            case 6:
            SDL_RenderCopy(renderer, textures->numbers.six, NULL, &numSlot[0]);
            break;
            case 7:
            SDL_RenderCopy(renderer, textures->numbers.seven, NULL, &numSlot[0]);
            break;
            case 8:
            SDL_RenderCopy(renderer, textures->numbers.eight, NULL, &numSlot[0]);
            break;
            case 9:
            SDL_RenderCopy(renderer, textures->numbers.nine, NULL, &numSlot[0]);
        }    
    }
}

//Define como será mostrada cada medida do tempo de execução
//Sets how each metric for the execution time will be shown
void showTime(int time, int type, SDL_Rect *rect, SDL_Renderer *renderer, programTxtr *textures){
    int ones, tens, hundreds, aux = time;

    //Obtém cada dígito separadamente do tempo passado como parâmetro
    //Gets each digit separately from the time passed as parameter 
    hundreds = aux / 100;
    aux -= (hundreds * 100);
    tens = aux / 10;
    aux -= (tens * 10);
    ones = aux;

    //Divide o rect principal em "subrects" para renderizar cada número e medida
    //Divides the main rect in "subrects" to render each digit an metric
    SDL_Rect numSlots[3], text;
    numSlots[0] = *rect;
    numSlots[0].w = 20 * sizeMultiplier;
    numSlots[1] = numSlots[0];
    numSlots[1].x += numSlots[1].w;
    numSlots[2] = numSlots[1];
    numSlots[2].x += numSlots[2].w;

    text.w = 50 * sizeMultiplier;
    text.h = 30 * sizeMultiplier;

    //Checa cada digito, aplica sua devida textura e incrementa o índice de numSlot[].
    //Caso o dígito seja um zero à esquerda, o índice não será atualizado
    //Checks each digit, applies it’s respective texture and increments numSlot[]’s index.
    //If the digit is a zero to the left, the index is not incremented
    if(time < 1000){
        int i = 0;
        if(hundreds != 0){
            switch(hundreds){
                case 1:
                SDL_RenderCopy(renderer, textures->numbers.one, NULL, &numSlots[i]);
                break;
                case 2:
                SDL_RenderCopy(renderer, textures->numbers.two, NULL, &numSlots[i]);
                break;
                case 3:
                SDL_RenderCopy(renderer, textures->numbers.three, NULL, &numSlots[i]);
                break;
                case 4:
                SDL_RenderCopy(renderer, textures->numbers.four, NULL, &numSlots[i]);
                break;
                case 5:
                SDL_RenderCopy(renderer, textures->numbers.five, NULL, &numSlots[i]);
                break;
                case 6:
                SDL_RenderCopy(renderer, textures->numbers.six, NULL, &numSlots[i]);
                break;
                case 7:
                SDL_RenderCopy(renderer, textures->numbers.seven, NULL, &numSlots[i]);
                break;
                case 8:
                SDL_RenderCopy(renderer, textures->numbers.eight, NULL, &numSlots[i]);
                break;
                case 9:
                SDL_RenderCopy(renderer, textures->numbers.nine, NULL, &numSlots[i]);
            }
            i++;
        }
        switch(tens){
            case 0:
            if(hundreds == 0){
                i--;
            }
            else{
                SDL_RenderCopy(renderer, textures->numbers.zero, NULL, &numSlots[i]);
            }
            break;
            case 1:
            SDL_RenderCopy(renderer, textures->numbers.one, NULL, &numSlots[i]);
            break;
            case 2:
            SDL_RenderCopy(renderer, textures->numbers.two, NULL, &numSlots[i]);
            break;
            case 3:
            SDL_RenderCopy(renderer, textures->numbers.three, NULL, &numSlots[i]);
            break;
            case 4:
            SDL_RenderCopy(renderer, textures->numbers.four, NULL, &numSlots[i]);
            break;
            case 5:
            SDL_RenderCopy(renderer, textures->numbers.five, NULL, &numSlots[i]);
            break;
            case 6:
            SDL_RenderCopy(renderer, textures->numbers.six, NULL, &numSlots[i]);
            break;
            case 7:
            SDL_RenderCopy(renderer, textures->numbers.seven, NULL, &numSlots[i]);
            break;
            case 8:
            SDL_RenderCopy(renderer, textures->numbers.eight, NULL, &numSlots[i]);
            break;
            case 9:
            SDL_RenderCopy(renderer, textures->numbers.nine, NULL, &numSlots[i]);
        }
        i++;
        switch(ones){
            case 0:
            SDL_RenderCopy(renderer, textures->numbers.zero, NULL, &numSlots[i]);
            break;
            case 1:
            SDL_RenderCopy(renderer, textures->numbers.one, NULL, &numSlots[i]);
            break;
            case 2:
            SDL_RenderCopy(renderer, textures->numbers.two, NULL, &numSlots[i]);
            break;
            case 3:
            SDL_RenderCopy(renderer, textures->numbers.three, NULL, &numSlots[i]);
            break;
            case 4:
            SDL_RenderCopy(renderer, textures->numbers.four, NULL, &numSlots[i]);
            break;
            case 5:
            SDL_RenderCopy(renderer, textures->numbers.five, NULL, &numSlots[i]);
            break;
            case 6:
            SDL_RenderCopy(renderer, textures->numbers.six, NULL, &numSlots[i]);
            break;
            case 7:
            SDL_RenderCopy(renderer, textures->numbers.seven, NULL, &numSlots[i]);
            break;
            case 8:
            SDL_RenderCopy(renderer, textures->numbers.eight, NULL, &numSlots[i]);
            break;
            case 9:
            SDL_RenderCopy(renderer, textures->numbers.nine, NULL, &numSlots[i]);
        }

        //Posiciona a medida após a ultima casa utilizada
        //Positions the metrics after the last used slot
        text.x = numSlots[i].x + numSlots[i].w + 5 * sizeMultiplier;
        text.y = numSlots[i].y;
    }
    else{
    //Mostra "erro" caso o número seja grande demais
    //Renders “erro” if the number is too big
        text.x = (*rect).x;
        text.y = (*rect).y;
        SDL_RenderCopy(renderer, textures->info.time.error, NULL, &text);
        text.x += text.w + 5 * sizeMultiplier;
    }
    //Mostra a medida
    //Renders the metric
    switch(type){
        case 1:
        SDL_RenderCopy(renderer, textures->info.time.hour, NULL, &text);
        break;
        case 2:
        SDL_RenderCopy(renderer, textures->info.time.min, NULL, &text);
        break;
        case 3:
        SDL_RenderCopy(renderer, textures->info.time.sec, NULL, &text);
        break;
        case 4:
        SDL_RenderCopy(renderer, textures->info.time.milisec, NULL, &text);
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Sorting Algorithms Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if(window == NULL){
        std::cout << "Could not create window: "<< SDL_GetError()<< std::endl;
        return 1;
    }

    SDL_GetWindowSize(window, &WIDTH, &HEIGHT);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    //Procedimento básico para iniciar um programa usando SDL2
    //Basic procedure for inicializing a program using SDL2

    programTxtr textures;
    load_textures(renderer, &textures);

    const int maxOption = 6;
    const int maxSize = 5000;
    const int minSize = 10;
    int size = 100;
    //Controle do array size
    //Control the array size

    bars vec[maxSize];
    //Vetor que armazena tanto os valores quando as informações de cada barra
    //Array that stores the values and info of each bar

    int screen = 0;
    //Controle da tela a ser mostrada (menu ou visualizador).
    //Também identifica o algorítmo usado (1 a 5)
    //Controls wich screen is being shown (menu or visualizer)
    //Also identifies the used algorithm (1 to 5)

    int currentOption = 1, temporaryDelay = 0;
    //Controle da seleção dos algorítmos
    //Control the algorithm selection
    
    int lastWIDTH = 0, lastHEIGHT = 0;
    //Usado para checar se o tamanho da tela mudou
    //Used to check if the window size has changed

    bool leftMouseDown, escDown;
    //Controle de clicks em teclas/mouse
    //Control clicks/key presses

    bool shown, sorted, sortAborted, delaySelected = false;
    //Controle das opções e do estado do visualizador
    //Control the options and state of the visualizer 

    int up1selected = 0, up10selected = 0, up100selected = 0, maxSelected = 0;
    int down1selected = 0, down10selected = 0, down100selected = 0, minSelected = 0;
    int nextSelected = 0, prevSelected = 0;
    //Controle de clicks nos botões do menu
    //Control button clicks on the menu
    const int selectDelay = 4;
    //Número de ciclos que botões pressionados tem a cor diferente
    //Number of cycles that pressed buttons have a different color
   

    uint64_t sortStartTime, sortEndTime, sortTotalTime;
    int milisec, sec, min, hour;
    //Guardam do tempo de execução do algorítmo
    //Store the algorithm’s execution time

    uint32_t frameStart;
    int frameTime;
    const int FPS = 30, frameDelay = 1000/FPS;
    //Controle da taxa de quadros por segundo (fps)
    //Control the frame rate (fps)

    SDL_Rect algorithmOption;
    SDL_Rect nextOption, previousOption;
    SDL_Rect sizeText;
    SDL_Rect vecSizeDisplay;
    SDL_Rect up1, up10, up100;  
    SDL_Rect down1, down10, down100;
    SDL_Rect maxButton, minButton; 
    SDL_Rect startButton;
    SDL_Rect credits;
    //Elementos do menu
    //Menu elements
    
    SDL_Rect delayOption;
    SDL_Rect randomizeButton;
    SDL_Rect startSortButton;
    SDL_Rect timeInfo[5];
    SDL_Rect quit;
    SDL_Rect underBars;
    //Elementos do visualizador
    //Visualizer elements

    SDL_Rect mouse;
    mouse.h = 1;
    mouse.w = 1;
    //Hitbox do cursor
    //Cursor’s hitbox

    SDL_Rect intersection;
    //Auxiliar para a detecção de colisões entre o cursor e os botões
    //Auxiliar for collision detection between the cursor and buttons 

    srand(time(NULL));

    bool running = true;
    //Início do ciclo
    //Cycle start
    while(running)
    {
        frameStart = SDL_GetTicks();

        if(programQuit)
        {
            running = false;
        }
        leftMouseDown = false;
        escDown = false;

        //Toma conta das interações do usuário (clicks, teclas, ...)
        //Handles user interaction (clicks, keys, ...)
        if(SDL_PollEvent(&event))
        {
            if(SDL_QUIT == event.type)
            {
                running = false;
            }
            else if(SDL_MOUSEBUTTONDOWN == event.type)
            {
                if(SDL_BUTTON_LEFT == event.button.button)
                {
                    leftMouseDown = true;
                }
            }
            else if(SDL_MOUSEMOTION == event.type)
            {
                SDL_GetMouseState( &mouse.x, &mouse.y);
            }
            else if(SDL_KEYDOWN == event.type)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    escDown = true;
                }
            }            
        }

        SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
        //Atualiza a posição e tamanho de cada elemento de acordo com o tamanho da janela
        //Updates each element’s size and position acorrding to the window size
        if(lastHEIGHT != HEIGHT || lastWIDTH != WIDTH)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            //Calcula a proporção da tela para reposicionar e redimensionar os elementos
            //Calculates screen the proportion to reposition and resize the elements
            if(HEIGHT < 900 || WIDTH < 1100)
            { 
                if(900 - HEIGHT <= 1100 - WIDTH)
                {
                    sizeMultiplier = float(WIDTH) / 1100;
                }
                else
                {
                    sizeMultiplier = float(HEIGHT) / 900;
                }
                std::cout << "Proportion: " << sizeMultiplier << std::endl;
            }
            else
            {
                sizeMultiplier = 1;
            }

            std::cout << "Window size: " << WIDTH << " : " << HEIGHT << std::endl; 

            delayOption.w = 400 * sizeMultiplier;
            delayOption.h = 50 * sizeMultiplier;
            delayOption.x = 20 * sizeMultiplier;
            delayOption.y = 20 * sizeMultiplier;

            randomizeButton.w = 400 * sizeMultiplier;
            randomizeButton.h = 50 * sizeMultiplier;
            randomizeButton.x = 20 * sizeMultiplier;
            randomizeButton.y = delayOption.h + delayOption.y + 2 * sizeMultiplier;

            startSortButton.w = 400 * sizeMultiplier;
            startSortButton.h = 50 * sizeMultiplier;
            startSortButton.x = 20 * sizeMultiplier;
            startSortButton.y = randomizeButton.h + randomizeButton.y + 2 * sizeMultiplier;

            quit.w = 500 * sizeMultiplier;
            quit.h = 50 * sizeMultiplier;
            quit.x = WIDTH - quit.w - 20 * sizeMultiplier;
            quit.y = 20 * sizeMultiplier;

            underBars.w = WIDTH;
            underBars.h = 24;
            underBars.x = 0;
            underBars.y = HEIGHT - underBars.h;

            algorithmOption.h = 200 * sizeMultiplier;
            algorithmOption.w = 600 * sizeMultiplier;
            algorithmOption.y = (HEIGHT/2) - 325 * sizeMultiplier;
            algorithmOption.x = (WIDTH/2) - 300 * sizeMultiplier;

            nextOption.w = 100 * sizeMultiplier;
            nextOption.h = 100 * sizeMultiplier;
            nextOption.x = algorithmOption.x + algorithmOption.w + 30 * sizeMultiplier;
            nextOption.y = algorithmOption.y + ((algorithmOption.h - nextOption.h)/2);

            previousOption.w = 100 * sizeMultiplier;
            previousOption.h = 100 * sizeMultiplier;
            previousOption.x = algorithmOption.x - previousOption.w - 30 * sizeMultiplier;
            previousOption.y = algorithmOption.y + ((algorithmOption.h - previousOption.h)/2);

            sizeText.w = 200 * sizeMultiplier;
            sizeText.h = 40 * sizeMultiplier;
            sizeText.y = algorithmOption.y + 250 * sizeMultiplier;
            sizeText.x = (WIDTH/2) - 100 * sizeMultiplier;

            vecSizeDisplay.h = 150 * sizeMultiplier;
            vecSizeDisplay.w = 400 * sizeMultiplier;
            vecSizeDisplay.y = sizeText.y + 20 * sizeMultiplier;
            vecSizeDisplay.x = (WIDTH/2) - 200 * sizeMultiplier;
        
            up100.w = 100 * sizeMultiplier;
            up100.h = 100 * sizeMultiplier;
            up100.x = vecSizeDisplay.x + vecSizeDisplay.w + 20 * sizeMultiplier;
            up100.y = vecSizeDisplay.y + ((vecSizeDisplay.h - up100.h)/2);

            up10.w = 80 * sizeMultiplier;
            up10.h = 80 * sizeMultiplier;
            up10.x = up100.x + up100.w + 20 * sizeMultiplier;
            up10.y = up100.y + ((up100.h - up10.h)/2);

            up1.w = 60 * sizeMultiplier;
            up1.h = 60 * sizeMultiplier;
            up1.x = up10.x + up10.w + 20 * sizeMultiplier;
            up1.y = up10.y + ((up10.h - up1.h)/2);

            maxButton.w = 70 * sizeMultiplier;
            maxButton.h = 35 * sizeMultiplier;
            maxButton.x = WIDTH/2 + 20 * sizeMultiplier;
            maxButton.y = vecSizeDisplay.y + vecSizeDisplay.h;

            down100.w = 100 * sizeMultiplier;
            down100.h = 100 * sizeMultiplier;
            down100.x = vecSizeDisplay.x - down100.w - 20 * sizeMultiplier;
            down100.y = vecSizeDisplay.y + ((vecSizeDisplay.h - down100.h)/2);

            down10.w = 80 * sizeMultiplier;
            down10.h = 80 * sizeMultiplier;
            down10.x = down100.x - down10.w - 20 * sizeMultiplier;
            down10.y = down100.y + ((down100.h - down10.h)/2);

            down1.w = 60 * sizeMultiplier;
            down1.h = 60 * sizeMultiplier;
            down1.x = down10.x - down1.w - 20 * sizeMultiplier;
            down1.y = down10.y + ((down10.h - down1.h)/2);

            minButton.w = 70 * sizeMultiplier;
            minButton.h = 35 * sizeMultiplier;
            minButton.x = WIDTH/2 - minButton.w - 20 * sizeMultiplier;
            minButton.y = vecSizeDisplay.y + vecSizeDisplay.h;

            startButton.w = 250 * sizeMultiplier;
            startButton.h = 150 * sizeMultiplier;
            startButton.x = WIDTH/2 - startButton.w/2;
            startButton.y = vecSizeDisplay.y + 220 * sizeMultiplier;
            
            timeInfo[0].w = 400 * sizeMultiplier;
            timeInfo[0].h = 30 * sizeMultiplier;

            credits.w = 300 * sizeMultiplier;
            credits.h = 30 * sizeMultiplier;
            credits.x = 2 * sizeMultiplier;
            credits.y = HEIGHT - credits.h - 2 * sizeMultiplier;

            lastWIDTH = WIDTH;
            lastHEIGHT = HEIGHT;
        }

        if(screen == 0)//Menu
        {
            SDL_SetWindowResizable(window, SDL_TRUE);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            //Reseta a cor de renderização de cada textura para o padrão
            //Resets each texture’s rendering color to default 
            SDL_SetTextureColorMod(textures.buttons.next, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.previous, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.up.hundred, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.up.ten, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.up.one, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.up.max, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.down.hundred, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.down.ten, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.down.one, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.down.min, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.start, 255, 255, 255);

            //Detecta e mostra a interseção do cursor com cada botão e toma conta do que acontece quando há um click
            //Detects and displays the intersection between the cursor and a button and handles what happens when there is a click
            if(SDL_IntersectRect(&mouse, &nextOption, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.next, 200, 200, 200);
                if(leftMouseDown)
                {
                    nextSelected = selectDelay;
                    currentOption++;
                    if(currentOption > maxOption)
                    {
                        currentOption = 1;
                    }
                    std::cout << "Option number: " << currentOption << std::endl;                        
                }

            }
            else if(SDL_IntersectRect(&mouse, &previousOption, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.previous, 200, 200, 200);
                if(leftMouseDown)
                {
                    prevSelected = selectDelay;
                    currentOption--;
                    if(currentOption < 1)
                    {
                        currentOption = maxOption;
                    }
                    std::cout << "Option number: " << currentOption << std::endl;                        
                }

            }
            else if(SDL_IntersectRect(&mouse, &up1, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.up.one, 200, 200, 200);
                if(leftMouseDown)
                {
                    up1selected = selectDelay;
                    size++;
                    if(size > maxSize)
                    {
                        size -= size - maxSize;
                    }
                    std::cout << "array size: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &up10, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.up.ten, 200, 200, 200);
                if(leftMouseDown)
                {
                    up10selected = selectDelay;
                    size += 10;
                    if(size > maxSize)
                    {
                        size -= size - maxSize;
                    }
                    std::cout << "array size: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &up100, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.up.hundred, 200, 200, 200);
                if(leftMouseDown)
                {
                    up100selected = selectDelay;
                    size += 100;
                    if(size > maxSize)
                    {
                        size -= size - maxSize;
                    }
                    std::cout << "array size: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &maxButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.up.max, 200, 200, 200);
                if(leftMouseDown)
                {
                    maxSelected = selectDelay;
                    size = maxSize;
                    std::cout << "array size: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &down1, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.down.one, 200, 200, 200);
                if(leftMouseDown)
                {
                    down1selected = selectDelay;
                    size--;
                    if(size < minSize)
                    {
                        size += minSize - size;
                    }
                    std::cout << "array size: " << size << std::endl;                        
                }

            }
            else if(SDL_IntersectRect(&mouse, &down10, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.down.ten, 200, 200, 200);
                if(leftMouseDown)
                {
                    down10selected = selectDelay;
                    size -= 10;
                    if(size < minSize)
                    {
                        size += minSize - size;
                    }
                    std::cout << "array size: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &down100, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.down.hundred, 200, 200, 200);
                if(leftMouseDown)
                {
                    down100selected = selectDelay;
                    size -= 100;
                    if(size < minSize){
                        size += minSize - size;
                    }
                    std::cout << "array size: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &minButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.down.min, 200, 200, 200);
                if(leftMouseDown)
                {
                    minSelected = selectDelay;
                    size = minSize;
                    std::cout << "array size: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &startButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.start, 0, 230, 0);
                if(leftMouseDown)
                {
                    screen = currentOption;
                    std::cout << "Option: " << currentOption << "\nSize: " << size << std::endl;
                    shown = false;
                    sortAborted = false;
                    delaySelected = false;
                    sorted = false; 
                    temporaryDelay = 0;
                    delay = 0;
                    textures.buttons.delay.temporary = textures.buttons.delay.off;    
                    inicialize(vec, size);
                    randomize(vec, size);
                    setUpBars(vec, size);
                }
                
            }

            //Troca a cor dos botões caso haja um click
            //Changes the button colors in case a click happend
            if(nextSelected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.next, 180, 40, 40);
                nextSelected--;
            }
            if(prevSelected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.previous, 180, 40, 40);
                prevSelected--;
            }
            if(up1selected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.up.one, 180, 40, 40);
                up1selected--;
            }
            if(up10selected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.up.ten, 180, 40, 40);
                up10selected--;
            }
            if(up100selected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.up.hundred, 180, 40, 40);
                up100selected--;
            }
            if(maxSelected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.up.max, 180, 40, 40);
                maxSelected--;
            }
            if(down1selected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.down.one, 180, 40, 40);
                down1selected--;
            }
            if(down10selected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.down.ten, 180, 40, 40);
                down10selected--;
            }
            if(down100selected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.down.hundred, 180, 40, 40);
                down100selected--;
            }
            if(minSelected > 0)
            {
                SDL_SetTextureColorMod(textures.buttons.down.min, 180, 40, 40);
                minSelected--;
            }
            //Mostra o nome de cada algorítmo
            //Displays each algorithm’s name
            switch(currentOption)
            {
                case 1:
                SDL_RenderCopy(renderer, textures.names.bubble, NULL, &algorithmOption);
                break;
                case 2:
                SDL_RenderCopy(renderer, textures.names.selection, NULL, &algorithmOption);
                break;
                case 3:
                SDL_RenderCopy(renderer, textures.names.insertion, NULL, &algorithmOption);
                break;
                case 4:
                SDL_RenderCopy(renderer, textures.names.merge, NULL, &algorithmOption);
                break;
                case 5:
                SDL_RenderCopy(renderer, textures.names.quick, NULL, &algorithmOption);
                break;
                case 6:
                SDL_RenderCopy(renderer, textures.names.heap, NULL, &algorithmOption);
                break;
            }

            //Renderizando todos os elementos do menu
            //Rendering all the menu elements
            showSize(size, &vecSizeDisplay, renderer, &textures);  
            
            SDL_RenderCopy(renderer, textures.buttons.next, NULL, &nextOption);
            SDL_RenderCopy(renderer, textures.buttons.previous, NULL, &previousOption);

            SDL_RenderCopy(renderer, textures.buttons.up.hundred, NULL, &up100);
            SDL_RenderCopy(renderer, textures.buttons.up.ten, NULL, &up10);
            SDL_RenderCopy(renderer, textures.buttons.up.one, NULL, &up1);
            SDL_RenderCopy(renderer, textures.buttons.up.max, NULL, &maxButton);

            SDL_RenderCopy(renderer, textures.buttons.down.hundred, NULL, &down100);
            SDL_RenderCopy(renderer, textures.buttons.down.ten, NULL, &down10);
            SDL_RenderCopy(renderer, textures.buttons.down.one, NULL, &down1);
            SDL_RenderCopy(renderer, textures.buttons.down.min, NULL, &minButton);

            SDL_RenderCopy(renderer, textures.buttons.start, NULL, &startButton);
            SDL_RenderCopy(renderer, textures.info.size, NULL, &sizeText);
            SDL_RenderCopy(renderer, textures.credits, NULL, &credits);

            SDL_RenderPresent(renderer);

        }

        else//Visualizer
        {
            SDL_SetWindowResizable(window, SDL_FALSE);

            SDL_SetTextureColorMod(textures.buttons.sort, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.randomize, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.delay.temporary, 255, 255, 255);
            
            //Renderiza o vetor pela primeira vez após entrar na tela de visualização
            //Renders the bars for the first time after entering the visualizer screen
            if(!shown)
            {
                inicialize(vec, size);
                randomize(vec, size);
                setUpBars(vec, size);
                shown = true;
            }
            //Habilita/Desabilita o delay
            //Turns the delay on and off
            if(SDL_IntersectRect(&mouse, &delayOption, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.delay.temporary, 225, 225, 225);
                if(leftMouseDown)
                {
                    if(!delaySelected)
                    {
                        std::cout << "Delay on\n";
                        delaySelected = true;
                        temporaryDelay = 5000/size;
                        textures.buttons.delay.temporary = textures.buttons.delay.on;
                    }
                    else
                    {
                        std::cout << "Delay off\n";
                        delaySelected = false;
                        temporaryDelay = 0;
                        textures.buttons.delay.temporary = textures.buttons.delay.off;
                    }    
                }
            }

            else if(SDL_IntersectRect(&mouse, &startSortButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.sort, 225, 225, 225);
                //Inicia o algorítmo
                //Starts the algorithm
                if(leftMouseDown)
                {
                    if(!sorted)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &delayOption);
                        SDL_RenderFillRect(renderer, &randomizeButton);
                        SDL_RenderFillRect(renderer, &startSortButton);
                        //Esconde os botõe
                        //Hides the buttons

                        sortStartTime = getTime();
                        delay = temporaryDelay;
                        if(screen == 1)
                        {
                            bubbleSort(vec, size, &sortAborted, renderer, &quit, &textures);
                        }
                        else if(screen == 2)
                        {
                            selectionSort(vec, size, &sortAborted, renderer, &quit, &textures);
                        }
                        else if(screen == 3)
                        {
                            insertionSort(vec, size, &sortAborted, renderer, &quit, &textures);
                        }
                        else if(screen == 4)
                        {
                            mergeSort(vec, 0, size - 1, size, &sortAborted, renderer, &quit, &textures);
                        }
                        else if(screen == 5)
                        {
                            quickSort(vec, 0, size - 1, size, &sortAborted, renderer, &quit, &textures);
                        }
                        else if(screen == 6)
                        {
                            heapsort(vec, size, &sortAborted, renderer, &quit, &textures);
                        }
                        sorted = true;
                        if(!sortAborted)
                        {
                            sortEndTime = getTime();
                            showCompleteVec(vec, size, &sortAborted, &quit, &textures, renderer);
                            sorted = true;

                            sortTotalTime = sortEndTime - sortStartTime;
                            milisec = 0, sec = 0, min = 0, hour = 0;
                            //Converte o tempo total de milisegundos para horas, minutos, segundos e milisegundos
                            //Converts the total execution time from miliseconds to hours, minutes, seconds and milisecods
                            milisec = sortTotalTime % 1000;
                            sec = sortTotalTime / 1000;
                            min = sec / 60;
                            sec = sec % 60;
                            hour = min / 60;
                            min = min % 60;

                            std::cout << "Executed in:\n"
                            << milisec << " ms\n"
                            << sec << " s\n"
                            << min << " min\n"
                            << hour << " h\n";
                        }
                        
                    }    
                } 
            }
            //Randomiza o vetor
            //Randomizes the array
            else if(SDL_IntersectRect(&mouse, &randomizeButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.randomize, 225, 225, 225);
                if(leftMouseDown)
                {
                    inicialize(vec, size);
                    randomize(vec, size);
                    setUpBars(vec, size);
                    sorted = false;    
                }
            }
            //Volta para o menu
            //Goes back to the menu
            else if(escDown || sortAborted){
                screen = 0;
                escDown = sortAborted = false;
            }
            
            showVec(vec, size, NULL, &quit, &textures, renderer, false, sorted);
            SDL_RenderCopy(renderer, textures.buttons.delay.temporary, NULL, &delayOption);  
            SDL_RenderCopy(renderer, textures.buttons.randomize, NULL, &randomizeButton);
            if(!sorted)
            {
                SDL_RenderCopy(renderer, textures.buttons.sort, NULL, &startSortButton); 
            }
            else{
                timeInfo[0].x = startSortButton.x;
                timeInfo[0].y = startSortButton.y;
                for(int i = 1; i < 5; i++){
                    timeInfo[i] = timeInfo[i - 1];
                    timeInfo[i].y += timeInfo[i].h;
                }

                SDL_RenderCopy(renderer, textures.info.time.phrase, NULL, &timeInfo[0]);

                int i = 1;
                if(hour != 0){
                    showTime(hour, 1, &timeInfo[i], renderer, &textures);
                    i++;
                }
                if(min != 0){
                    showTime(min, 2, &timeInfo[i], renderer, &textures);
                    i++;
                }
                if(sec != 0){
                    showTime(sec, 3, &timeInfo[i], renderer, &textures);
                    i++;
                }
                if(milisec != 0){
                    showTime(milisec, 4, &timeInfo[i], renderer, &textures);
                    i++;
                }  
            }
            SDL_RenderPresent(renderer);
        }
        
        //Limita a taxa de quadros por segundo para 60 fps
        //Limits the frame rate to 60 fps
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyWindow(window);

    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();

    return EXIT_SUCCESS;   
}