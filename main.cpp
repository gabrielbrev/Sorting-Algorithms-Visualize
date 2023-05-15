#include <iostream>
#include <chrono>
#include <thread>
#include "src/include/SDL2/SDL.h"

int WIDTH = 800, HEIGHT = 600;

int delay = 0;
bool programQuit = false;

float sizeMultiplier = 1;

struct time{
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
    struct time time;
};
struct name_textures{
    SDL_Texture *bubble;
    SDL_Texture *selection;
    SDL_Texture *insertion;
    SDL_Texture *merge;
    SDL_Texture *quick;
};
struct size_buttons{
    SDL_Texture *one;
    SDL_Texture *ten;
    SDL_Texture *hundred;
    SDL_Texture *max;
    SDL_Texture *min;
};
struct delay_button{
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
    struct delay_button delay;
    struct size_buttons up;
    struct size_buttons down;
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

void load_textures(SDL_Renderer *renderer, programTxtr *textures){//Carrega as texturas do programa
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

//Mostra os valores do vetor na tela
void showVec(int vec[], float vecSize, SDL_Renderer *renderer, programTxtr *textures, bool *abort, int cmp1 = -1, int cmp2 = -1, int base = -1)
{
    SDL_Rect rect, quit;
    quit.w = 500 * sizeMultiplier;
    quit.h = 50 * sizeMultiplier;
    quit.x = WIDTH - quit.w - 20 * sizeMultiplier;
    quit.y = 20 * sizeMultiplier;

    float size = vecSize;
    float rectWidth = ((WIDTH - 50)/size);
    float spacing = 25;
    float gap;

    //Calcula o espaçamento entre barras se exixtir
    if(rectWidth >= 3)
    {
        gap = rectWidth * 0.2;
    }
    else
    {
        gap = 0;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Calcula e mostra a posição e tamanho de cada barra (valor)
    for(int i = 0; i < size; i++)
    {
        rect.w = rectWidth - gap * sizeMultiplier;
        rect.h = ((HEIGHT * 0.75)/size) * vec[i];
        rect.x = spacing + (rectWidth * i) + gap * sizeMultiplier;
        rect.y = HEIGHT - rect.h - 25;
        if(i == base)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else if(i == cmp1)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else if(i == cmp2)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderCopy(renderer, textures->info.quit, NULL, &quit);
    SDL_RenderPresent(renderer);
    SDL_Delay(delay);
}

//Completa as barras com a cor verde gradativamente
void showCompleteVec(int vec[], int vecSize, SDL_Renderer *renderer, programTxtr *textures, bool *abort)
{
    SDL_Event event;

    SDL_Rect rect, quit;
    quit.w = 500 * sizeMultiplier;
    quit.h = 50 * sizeMultiplier;
    quit.x = WIDTH - quit.w - 20 * sizeMultiplier;
    quit.y = 20 * sizeMultiplier;

    float size = float(vecSize);
    float rectWidth = ((WIDTH - 50)/size);
    float spacing = 25;
    float gap;
    int complete = 1;  
    int tempDelay;

    if(rectWidth >= 3)
    {
        gap = rectWidth * 0.2;
    }
    else
    {
        gap = 0;
    }

    for(int c = 0; c < size; c++)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(SDLK_ESCAPE == event.key.keysym.sym)
                {
                    delay = 0;
                    *abort = true;
                    int complete = 1;
                    for(int c = 0; c < vecSize; c++){
                        if(vec[c] != complete)
                        {
                            vec[c] = complete;
                        }
                        complete++;
                    }
                    return;
                }
            }   
            else if(event.type == SDL_QUIT)
            {
                programQuit = true;
                *abort = true;
                return;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(int i = 0; i < size; i++)
        {
            rect.w = rectWidth - gap * sizeMultiplier;
            rect.h = ((HEIGHT * 0.75)/size) * vec[i];
            rect.x = spacing + (rectWidth * i) + gap * sizeMultiplier;
            rect.y = HEIGHT - rect.h - 25;
            if(i <= complete)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &rect);
        }
        complete++;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderCopy(renderer, textures->info.quit, NULL, &quit);
        SDL_RenderPresent(renderer);
        if(size < 2000)
        {
            tempDelay = 250/size;
            SDL_Delay(tempDelay);
        }
    }
}

//Zera os valores do vetor
void inicialize(int vec[], int vecSize)
{
    for(int i = 0; i < vecSize; i++)
    {
        vec[i] = 0;
    }
}

//Aleatoriza os valores do vetor de acordo com seu tamanho
void randomize(int vec[], int vecSize)
{
    int num;
    bool invec;
    for(int i = 0; i < vecSize; i++)
    {
        do{
            invec = false;
            num = rand() % vecSize + 1;
            for(int j = 0; j < vecSize; j++)
            {
                if(vec[j] == num)
                {
                    invec = true;
                }
            }
        }while(invec);
        vec[i] = num;
    }
}

void insertionSort(int vec[], int vecSize, SDL_Renderer *renderer, programTxtr *textures, bool *abort)
{
    SDL_Event event;
    int aux, a, b;
    for(int i = 0; i < vecSize - 1; i++)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(SDLK_ESCAPE == event.key.keysym.sym)
                {
                    delay = 0;
                    *abort = true;
                    int complete = 1;
                    for(int c = 0; c < vecSize; c++){
                        if(vec[c] != complete)
                        {
                            vec[c] = complete;
                        }
                        complete++;
                    }
                    return;
                }
            }  
            else if(event.type == SDL_QUIT)
            {
                programQuit = true;
                *abort = true;
                return;
            }         
        }

        if(vec[i + 1] < vec[i])
        {
            a = i;
            b = i + 1;
            while(vec[a] > vec[b] && a >= 0)
            {
                aux = vec[a];
                vec[a] = vec[b];
                vec[b] = aux;
                a--;
                b--;
                showVec(vec, vecSize, renderer, textures, abort, b, a);
            }
        }
        showVec(vec, vecSize, renderer, textures, abort, i + 1, i);
    }
}

void bubbleSort(int vec[], int vecSize, SDL_Renderer * renderer, programTxtr *textures, bool *abort)
{
    SDL_Event event;
    int aux;
    for(int i = 0; i < vecSize; i++)
    {
        
        for(int j = i; j < vecSize; j++)
        {
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_KEYDOWN)
                {
                    if(SDLK_ESCAPE == event.key.keysym.sym)
                    {
                        delay = 0;
                        *abort = true;
                        int complete = 1;
                        for(int c = 0; c < vecSize; c++){
                            if(vec[c] != complete)
                            {
                                vec[c] = complete;
                            }
                            complete++;
                        }
                        return;
                    }
                }
                else if(event.type == SDL_QUIT)
                {
                    programQuit = true;
                    *abort = true;
                    return;
                }   
            }
            if(vec[i] > vec[j])
            {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
            showVec(vec, vecSize, renderer, textures, abort, i, j);
        }
    }

}

void swap(int *x, int *y)
{
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

void quickSort(int vec[], int start, int end, int vecSize, SDL_Renderer *renderer, programTxtr *textures, bool *abort)
{
    SDL_Event event;
    int i, j, key;
    if((end - start) < 2)
    {
        if((end - start == 1))
        {
            if(vec[start] > vec[end])
            {
                swap(&vec[start], &vec[end]);
                showVec(vec, vecSize, renderer, textures, abort, start, end);
            }
        }
    }
    else
    {
        i = start;
        j = end;
        key = vec[start];
        while(j > i)
        {   
            if(*abort){
                return;
            }
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_KEYDOWN)
                {
                    if(SDLK_ESCAPE == event.key.keysym.sym)
                    {
                        delay = 0;
                        *abort = true;
                        int complete = 1;
                        for(int c = 0; c < vecSize; c++){
                            if(vec[c] != complete)
                            {
                                vec[c] = complete;
                            }
                            complete++;
                        }
                        return;
                    }
                }   
                else if(event.type == SDL_QUIT)
                {
                    programQuit = true;
                    *abort = true;
                    return;
                }        
            }
            i++;
            showVec(vec, vecSize, renderer, textures, abort, i, j, start);
            while(vec[i] < key)
            {
                i++;
                showVec(vec, vecSize, renderer, textures, abort, i, j, start);
            }
            while(vec[j] > key)
            {
                j--;
                showVec(vec, vecSize, renderer, textures, abort, i, j, start);
            }
            if(j > i)
            {
                swap(&vec[i], &vec[j]);
                showVec(vec, vecSize, renderer, textures, abort, i, j, start);
            }
        }
        swap(&vec[start], &vec[j]);
        showVec(vec, vecSize, renderer, textures, abort, start, j);
        if(!*abort){
            quickSort(vec, start, j - 1, vecSize, renderer, textures, abort);
        }
        if(!*abort){
            quickSort(vec, j + 1, end, vecSize, renderer, textures, abort);
        }     
    }
}

void selectionSort(int vec[], int vecSize, SDL_Renderer * renderer, programTxtr *textures, bool *abort)
{
    SDL_Event event;
    int cmp, aux;
    for(int i = 0; i < vecSize - 1; i++)
    {
        cmp = i;
        for(int j = i + 1; j < vecSize; j++)
        {
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_KEYDOWN)
                {
                    if(SDLK_ESCAPE == event.key.keysym.sym)
                    {
                        int complete = 1;
                        delay = 0;
                        *abort = true;
                        for(int c = 0; c < vecSize; c++){
                            if(vec[c] != complete)
                            {
                                vec[c] = complete;
                            }
                            complete++;
                        }
                        return;
                    }
                }    
                else if(event.type == SDL_QUIT)
                {
                    programQuit = true;
                    *abort = true;
                    return;
                }               
            }           
            if(vec[j] < vec[cmp])
            {
                cmp = j;
            }
            if(vecSize < 1000)
            {
                showVec(vec, vecSize, renderer, textures, abort, cmp, j, i);
            }   
        } 
        aux = vec[i];
        vec[i] = vec[cmp];
        vec[cmp] = aux;
        showVec(vec, vecSize, renderer, textures, abort, i, cmp);
    }
    
}

void intercalate(int vec[], int start, int end, int mid, int vecSize, SDL_Renderer * renderer, programTxtr *textures, bool *abort){
    SDL_Event event;
    int i, aux[vecSize], freePos = start, start1 = start, start2 = mid + 1;
    while(start1 <= mid && start2 <= end && *abort == false){
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(SDLK_ESCAPE == event.key.keysym.sym)
                {
                    delay = 0;
                    *abort = true;
                    int complete = 1;
                    for(int c = 0; c < vecSize; c++){
                        if(vec[c] != complete)
                        {
                            vec[c] = complete;
                        }
                        complete++;
                    }
                    if(*abort == true)
                    {
                        return;
                    }
                }
            }    
            else if(event.type == SDL_QUIT)
            {
                programQuit = true;
                *abort = true;
                return;
            }               
        }
        if(vec[start1] > vec[start2]){
            aux[freePos] = vec[start2];
            start2++;
            if(start1 == start2)
            {
                showVec(vec, vecSize, renderer, textures, abort, start2, start1 - 1);
            }
            else
            {
                showVec(vec, vecSize, renderer, textures, abort, start2, start1);
            }
        }
        else{
            aux[freePos] = vec[start1];
            start1++;
            if(start1 == start2)
            {
                showVec(vec, vecSize, renderer, textures, abort, start2, start1 - 1);
            }
            else
            {
                showVec(vec, vecSize, renderer, textures, abort, start2, start1);
            }
        }
        freePos++;
    }
    if(*abort == false)
    {
        for(i = start1; i <= mid; i++){
            aux[freePos] = vec[i];
            freePos++;
            if(i == mid)
            {
                showVec(vec, vecSize, renderer, textures, abort, mid, i - 1);
            }
            else
            {
                showVec(vec, vecSize, renderer, textures, abort, mid, i);
            }
        }
        for(i = start2; i <= end; i++){
            aux[freePos] = vec[i];
            freePos++;
            if(i == end)
            {
                showVec(vec, vecSize, renderer, textures, abort, end, i - 1);
            }
            else
            {
                showVec(vec, vecSize, renderer, textures, abort, end, i);
            }
        }
        for(i = start; i <= end; i++){
            vec[i] = aux[i];
            if(i == end)
            {
                showVec(vec, vecSize, renderer, textures, abort, end, i - 1);
            }
            else
            {
                showVec(vec, vecSize, renderer, textures, abort, end, i);
            }
        }        
    }

}

void mergeSort(int vec[], int start, int end, int vecSize, SDL_Renderer * renderer, programTxtr *textures, bool *abort){
    int mid;
    if(*abort == true)
    {
        return;
    }    
    if(start < end)
    {
        mid = (start + end)/2;
        mergeSort(vec, start, mid, vecSize, renderer, textures, abort);
        mergeSort(vec, mid + 1, end, vecSize, renderer, textures, abort);
        intercalate(vec, start, end, mid, vecSize, renderer, textures, abort);
    }
}

//Mostra o tamanho atual do vetor
void showSize(int size, SDL_Rect *rect, SDL_Renderer *renderer, programTxtr *textures){
    int aux = size;
    int thousands, hundreds, tens, ones;

    //Extrai cada número individualmente
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
    
    //Checa cada número individualmente e renderiza suas texturas
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

//Mostra o tempo de execução para todas as medidas
void showTime(int time, int type, SDL_Rect *rect, SDL_Renderer *renderer, programTxtr *textures){
    int ones, tens, hundreds, aux = time;

    //Extrai cada número individualmente
    hundreds = aux / 100;
    aux -= (hundreds * 100);
    tens = aux / 10;
    aux -= (tens * 10);
    ones = aux;

    SDL_Rect numSlots[3], text;//Divide o rect principal em "subrects" para renderizar cada número e a medida após
    numSlots[0] = *rect;
    numSlots[0].w = 20 * sizeMultiplier;
    numSlots[1] = numSlots[0];
    numSlots[1].x += numSlots[1].w;
    numSlots[2] = numSlots[1];
    numSlots[2].x += numSlots[2].w;

    text.w = 50 * sizeMultiplier;
    text.h = 30 * sizeMultiplier;

    //Checa as casas decimais, renderiza e atualiza o número da casa a ser utilizada,
    //caso haja um zero à esquerda, a casa não é atualizada.
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
        text.x = numSlots[i].x + numSlots[i].w + 5 * sizeMultiplier;
        text.y = numSlots[i].y;
    }
    else{//Mostra "erro" caso o número seja grande demais
        text.x = (*rect).x;
        text.y = (*rect).y;
        SDL_RenderCopy(renderer, textures->info.time.error, NULL, &text);
        text.x += text.w + 5 * sizeMultiplier;
    }
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

uint64_t getTime(){//Pega o tempo passado após 01/01/1970 em milisegundos
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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
    //Procedimentos básicos para iniciar um programa usando SDL2

    programTxtr textures;
    load_textures(renderer, &textures);

    const int maxOption = 5;
    const int maxSize = 5000;
    const int minSize = 10;
    float size = 100;
    //Controle do tamanho do vetor

    int vec[maxSize];

    int screen = 0, lastScreen = 0;
    //Controle da tela a ser mostrada (menu ou visualizador).
    //Também identifica o algorítmo utilizado (1 a 5)

    int currentOption = 1, temporaryDelay = 0;
    //Controle da seleção dos algorítmos
    
    int lastWIDTH = 0, lastHEIGHT = 0;
    //Usado para checar se o tamanho da tela mudou

    bool leftMouseDown, escDown;
    //Controle de clicks em teclas/mouse

    bool shown, sorted, sortAborted, delaySelected = false;
    //Controle das opções/estado do visualizador

    int up1selected = 0, up10selected = 0, up100selected = 0, maxSelected = 0;
    int down1selected = 0, down10selected = 0, down100selected = 0, minSelected = 0;
    int nextSelected = 0, prevSelected = 0;
    //Controle de clicks nos botões do menu
    const int selectDelay = 4;
    //Quantidade de ciclos que a cor dos botões muda ao serem clicados

    uint64_t sortStartTime, sortEndTime, sortTotalTime;
    int milisec, sec, min, hour;
    //Controle do tempo de execução do algorítmo

    uint32_t frameStart;
    int frameTime;
    const int FPS = 30, frameDelay = 1000/FPS;
    //Controle da taxa de quadros por segundo (fps)

    SDL_Rect algorithmOption;
    SDL_Rect nextOption, previousOption;
    SDL_Rect sizeText;
    SDL_Rect vecSizeOption;
    SDL_Rect sizeSlot1, sizeSlot2, sizeSlot3, sizeSlot4;
    SDL_Rect up1, up10, up100;  
    SDL_Rect down1, down10, down100;
    SDL_Rect maxButton, minButton; 
    SDL_Rect startButton;
    SDL_Rect credits;
    //Elementos do menu
    
    SDL_Rect delayOption;
    SDL_Rect randomizeButton;
    SDL_Rect startSortButton;
    SDL_Rect timeInfo[5];
    //Elementos do visualizador

    SDL_Rect mouse;
    mouse.h = 1;
    mouse.w = 1;
    //Hitbox do mouse

    SDL_Rect intersection;
    //Auxiliar para a detecção de colisões entre o mouse e os botões

    bool running = true;

    while(running)//Início do programa
    {
        frameStart = SDL_GetTicks();

        if(programQuit)
        {
            running = false;
        }
        leftMouseDown = false;
        escDown = false;

        if(SDL_PollEvent(&event))//Toma conta das interações do usuário (clicks, teclas, ...)
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
        //Atualiza a posição de cada item do menu de acordo com o tamanho da janela
        if(lastHEIGHT != HEIGHT || lastWIDTH != WIDTH)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            if(HEIGHT < 900 || WIDTH < 1100)//Calcula a proporção da tela para reposicionar os itens;
            { 
                if(900 - HEIGHT <= 1100 - WIDTH)
                {
                    sizeMultiplier = float(WIDTH) / 1100;
                }
                else
                {
                    sizeMultiplier = float(HEIGHT) / 900;
                }
                std::cout << "Proporcao: " << sizeMultiplier << std::endl;
            }
            else
            {
                sizeMultiplier = 1;
            }

            std::cout << "Tamanho da janela: " << WIDTH << " : " << HEIGHT << std::endl; 

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

            vecSizeOption.h = 150 * sizeMultiplier;
            vecSizeOption.w = 400 * sizeMultiplier;
            vecSizeOption.y = sizeText.y + 20 * sizeMultiplier;
            vecSizeOption.x = (WIDTH/2) - 200 * sizeMultiplier;
        
            up100.w = 100 * sizeMultiplier;
            up100.h = 100 * sizeMultiplier;
            up100.x = vecSizeOption.x + vecSizeOption.w + 20 * sizeMultiplier;
            up100.y = vecSizeOption.y + ((vecSizeOption.h - up100.h)/2);

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
            maxButton.y = vecSizeOption.y + vecSizeOption.h;

            down100.w = 100 * sizeMultiplier;
            down100.h = 100 * sizeMultiplier;
            down100.x = vecSizeOption.x - down100.w - 20 * sizeMultiplier;
            down100.y = vecSizeOption.y + ((vecSizeOption.h - down100.h)/2);

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
            minButton.y = vecSizeOption.y + vecSizeOption.h;

            startButton.w = 250 * sizeMultiplier;
            startButton.h = 150 * sizeMultiplier;
            startButton.x = WIDTH/2 - startButton.w/2;
            startButton.y = vecSizeOption.y + 220 * sizeMultiplier;
            
            timeInfo[0].w = 400 * sizeMultiplier;
            timeInfo[0].h = 30 * sizeMultiplier;

            credits.w = 300 * sizeMultiplier;
            credits.h = 30 * sizeMultiplier;
            credits.x = 2 * sizeMultiplier;
            credits.y = HEIGHT - credits.h - 2 * sizeMultiplier;

            lastWIDTH = WIDTH;
            lastHEIGHT = HEIGHT;
        }
        
        if(lastScreen != screen)//Limpa a tela caso haja uma troca de interface (do menu para o visualizador e vice-versa)
        {
            lastScreen = screen;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }

        if(screen == 0)//Menu
        {
            SDL_SetWindowResizable(window, SDL_TRUE);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            //Reseta a cor de renderização dos botões para o padrão
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

            //Detecta e mostra a interseção do mouse com cada botão e toma conta dos clicks
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
                    std::cout << "Numero da opcao: " << currentOption << std::endl;                        
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
                    std::cout << "Numero da opcao: " << currentOption << std::endl;                        
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
                    std::cout << "Tamanho do vetor: " << size << std::endl;    
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
                    std::cout << "Tamanho do vetor: " << size << std::endl;    
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
                    std::cout << "Tamanho do vetor: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &maxButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.up.max, 200, 200, 200);
                if(leftMouseDown)
                {
                    maxSelected = selectDelay;
                    size = maxSize;
                    std::cout << "Tamanho do vetor: " << size << std::endl;    
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
                    std::cout << "Tamanho do vetor: " << size << std::endl;                        
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
                    std::cout << "Tamanho do vetor: " << size << std::endl;    
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
                    std::cout << "Tamanho do vetor: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &minButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.down.min, 200, 200, 200);
                if(leftMouseDown)
                {
                    minSelected = selectDelay;
                    size = minSize;
                    std::cout << "Tamanho do vetor: " << size << std::endl;    
                }
                
            }
            else if(SDL_IntersectRect(&mouse, &startButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.start, 0, 230, 0);
                if(leftMouseDown)
                {
                    screen = currentOption;
                    std::cout << "Opcao: " << currentOption << "\nTamanho: " << size << std::endl;
                    inicialize(vec, size);
                    randomize(vec, size);
                    shown = false;
                    sortAborted = false;
                    delaySelected = false;
                    sorted = false; 
                    temporaryDelay = 0;
                    delay = 0;
                    textures.buttons.delay.temporary = textures.buttons.delay.off;     
                }
                
            }

            //Troca a cor dos botões caso haja um click
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

            switch(currentOption)//Mostra o nome de cada algorítmo
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
                break;//Presente para caso haja a implementação de um novo algorítmo
            }

            //Renderizando todos os elementos do menu
            showSize(size, &vecSizeOption, renderer, &textures);  
            
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

        else//Visualizador de algorítmos
        {
            SDL_SetWindowResizable(window, SDL_FALSE);

            SDL_SetTextureColorMod(textures.buttons.sort, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.randomize, 255, 255, 255);
            SDL_SetTextureColorMod(textures.buttons.delay.temporary, 255, 255, 255);

            if(!shown)//Mostra o vetor pela primeira vez após entrar na tela de visualização
            {
                inicialize(vec, size);
                randomize(vec, size);
                shown = true;
            }
            //Habilita/Desabilita o delay
            if(SDL_IntersectRect(&mouse, &delayOption, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.delay.temporary, 225, 225, 225);
                if(leftMouseDown)
                {
                    if(!delaySelected)
                    {
                        std::cout << "Delay habilitado\n";
                        delaySelected = true;
                        temporaryDelay = 5000/size;
                        textures.buttons.delay.temporary = textures.buttons.delay.on;
                    }
                    else
                    {
                        std::cout << "Delay desabilitado\n";
                        delaySelected = false;
                        temporaryDelay = 0;
                        textures.buttons.delay.temporary = textures.buttons.delay.off;
                    }    
                }
                
            }

            
            else if(SDL_IntersectRect(&mouse, &startSortButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.sort, 225, 225, 225);
                if(leftMouseDown)//Inicia o algorítmo
                {
                    if(!sorted)
                    {
                        sortStartTime = getTime();
                        delay = temporaryDelay;
                        if(screen == 1)
                        {
                            bubbleSort(vec, size, renderer, &textures, &sortAborted);
                            sorted = true;
                        }
                        else if(screen == 2)
                        {
                            selectionSort(vec, size, renderer, &textures, &sortAborted);
                            sorted = true;
                        }
                        else if(screen == 3)
                        {
                            insertionSort(vec, size, renderer, &textures, &sortAborted);
                            sorted = true;
                        }
                        else if(screen == 4)
                        {
                            mergeSort(vec, 0, size - 1, size, renderer, &textures, &sortAborted);
                            sorted = true;
                        }
                        else if(screen == 5)
                        {
                            quickSort(vec, 0, size - 1, size, renderer, &textures, &sortAborted);
                            sorted = true;
                        }
                        if(!sortAborted)
                        {
                            sortEndTime = getTime();
                            showCompleteVec(vec, size, renderer, &textures, &sortAborted);
                            sorted = true;

                            sortTotalTime = sortEndTime - sortStartTime;
                            milisec = 0, sec = 0, min = 0, hour = 0;
                            //Transforma o tempo total em milisegundos em horas, minutos, segundos e milisegundos
                            milisec = sortTotalTime % 1000;
                            sec = sortTotalTime / 1000;
                            min = sec / 60;
                            sec = sec % 60;
                            hour = min / 60;
                            min = min % 60;

                            std::cout << "executado em:\n"
                            << milisec << " ms\n"
                            << sec << " s\n"
                            << min << " min\n"
                            << hour << " h\n";
                        }
                        
                    }    
                } 
            }
            //Randomiza o vetor
            else if(SDL_IntersectRect(&mouse, &randomizeButton, &intersection))
            {
                SDL_SetTextureColorMod(textures.buttons.randomize, 225, 225, 225);
                if(leftMouseDown)
                {
                    inicialize(vec, size);
                    randomize(vec, size);
                    showVec(vec, size, renderer, &textures, &sortAborted);
                    sorted = false;    
                }
            }
            //Retorna para o menu
            else if(escDown || sortAborted)
            {
                screen = 0;
                escDown = sortAborted = false;
            }
            
            //As próximas linhas utilizam a mesma lógica da função showVec(),
            //porém a chamda da função faz com que os botões e as medidas não possam
            //ser renderizadas por conta da falta de parãmetros que seriam necessários (texturas, rects).
            //Caso os parâmetros fossem adicionados, tais elementos também seriam mostrados durante
            //a execução, o que não é o objetivo
            SDL_Rect rect, quit;
            quit.w = 500 * sizeMultiplier;
            quit.h = 50 * sizeMultiplier;
            quit.x = WIDTH - quit.w - 20 * sizeMultiplier;
            quit.y = 20 * sizeMultiplier;

            float rectWidth = ((WIDTH - 50)/size);
            float spacing = 25;
            float gap;

            if(rectWidth >= 3)
            {
                gap = rectWidth * 0.2;
            }
            else
            {
                gap = 0;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            for(int i = 0; i < size; i++)
            {
                rect.w = rectWidth - gap * sizeMultiplier;
                rect.h = ((HEIGHT * 0.75)/size) * vec[i];
                rect.x = spacing + (rectWidth * i) + gap * sizeMultiplier;
                rect.y = HEIGHT - rect.h - 25;
                if(!sorted){
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                }
                SDL_RenderDrawRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderCopy(renderer, textures.info.quit, NULL, &quit);
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
        
        //Limita a taxa de quadros por segundo
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