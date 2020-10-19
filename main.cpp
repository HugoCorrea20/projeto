#include<allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>	
#include<allegro5/allegro_primitives.h>

enum TECLAS {CIMA,BAIXO,DIREITA,ESQUERDA};

int main() {


	//--------variavel do jogo -----------
	const int largura_t = 640;
	const int altura_t = 480;
	int pos_x = 100;
	int pos_y = 100;
	bool fim = false;
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
	bool teclas[] = { false, false, false,false };

	//______________________________________

	//----INICIALIZAÇÃO DA ALLEGRO E DO DISPLAY ----
	ALLEGRO_DISPLAY* display = NULL;

	if (!al_init())
	{
		al_show_native_message_box(NULL, "AVISO!", "ERRO:", "ALLEGRO NÃO PODE SER INICIALIZADA", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	display = al_create_display(640, 480);

	if (!display)
	{
		al_show_native_message_box(NULL, "AVISO!", "ERRO:", "O DISPLAY NÃO PODE SER CRIADO!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//______________________________________________

	//--------INICIALIZAÇÃO DE ADDONS E INSTALAÇÕES------
	al_install_keyboard();

	//---------CRIAÇÃO DA FILA E DEMAIS DISPOSITIVOS----------
	fila_eventos = al_create_event_queue();
	al_init_primitives_addon();

	//________________________________________

	//-------REGISTRO DE SOURCES ------------
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(display));

	//_______________________________________

	//---------LOOP PRINCIPAL-----------------
	while (!fim)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(fila_eventos, &ev);

		//----------EVENTOS E LÓGICA DO JOGO -----------
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				fim = true;
			}
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				teclas[CIMA] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				teclas[BAIXO] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				teclas[DIREITA] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				teclas[ESQUERDA] = true;
				break;


			}

		}

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
					teclas[CIMA] = false;
					break;
			case ALLEGRO_KEY_DOWN:
				teclas[BAIXO] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				teclas[DIREITA] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				teclas[ESQUERDA] = false;
				break;	
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			fim = true;
		}

		pos_y -= teclas[CIMA] * 10;
		pos_y += teclas[BAIXO] * 10;
		pos_x -= teclas[ESQUERDA] * 10;
		pos_x += teclas[DIREITA] * 10;	
		//___________________________________________________

		//-----------DESENHO----------------

		al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 255, 0));
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

	}
		//______________________________________________________

		//------------FINALIZAÇÕES DO PROGRAMA-------------------
		al_destroy_display(display);
		al_destroy_event_queue(fila_eventos);


		//________________________________________________________
		return 0;
	}
	

