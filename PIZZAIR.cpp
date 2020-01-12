#include<iostream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

using namespace std;

//PROTOTIPOS DE LAS FUNCIONES
//funcion de menu principal
char PizzaMenu();

//funciones de menus de comidas
int PrincipalFood();
int FoodTickets();
int Drinks();

int main(){
	//DECLARACION DE VARIABLES 
	//contrase?a para el menu principal
	char password[]="delete", key[6];  
	int k = 0; 
	
	//pedimos la contrase?a para ingresar
	cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
	cout<<"Ingrese la clave: ";cin>>key;
	
	//hay solo 3 intentos para ingresar la contrase?a correcta
	while(k==0){
		
		//se compara si la contrase?a es correcta
		if(strcmp(password,key) == 0){ //compara las dos palabras: password y key 
			
			system("cls"); 
			PizzaMenu(); //se llama la funcion del menu principal si la contraseñña es correcta
		
		}
		
		else{     //si no son iguaes las palabras, le sigue pidiendo que ingrese la clave hasta que ingrese la correcta
			
			system("cls");
			cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
			cout<<"Ingrese la clave: ";cin>>key;
			
		}	
						
	}
	
	return 0;
}

//menu principal del sistema de despacho
char PizzaMenu(){
	//variables de la funcion
	char option;
	
	//nosbre de la pizzaria
	cout<<"PIZZAIR\n"<<endl;
	
	//menu de opciones
	cout<<"1-Agregar 1 pedido a domicilio\n2-Agregar 1 encargo en restaurante\n3-Ver pedidos a domicilio\n4-Ver encargos en restaurante\n5-Ver total de ventas\n"<<endl;
	
	//se pide una opcion a seleccionar
	cout<<"Opcion: ";cin>>option;
	
	return option;
}

//FUNCIONES DE LOS MENUS DE COMIDA

//funcion de platos principales
int PrincipalFood(){
	//variables declaradas
	int k = 0, A;
	char option;
	
	//while donde se muestra el menu de platos principales
	while(k==0){
		
		//MENU DE PLATOS PRINCIPALES			
		cout<<"PLATO PRINCIPAL:\n"<<endl;
		cout<<"1-Pizza\n2-Ensalada\n3-Pasta\n"<<endl;
		cout<<"Opcion: ";cin>>option;
		
		if(option == '1' || option == '2' || option == '3'){ //si la opcion se encuentra en el menu entra al if
			
			if(option == '1'){ //si la opcion fue 1 la funcion retorna 0
				A = 0;
				k = 1; //para salirse del ciclo se modifica el valor de k
			}
			else if(option == '2'){ //si fue 2 retorna 1
				A = 1;
				k = 1;
			}
			else{
				A = 2; //si fue 3 retorna 2
				k = 1;
			}
			
		}
		system("cls");	
	}
	return A;		
}

//funcion de menu de entradas
int FoodTickets(){
	//variables de la funcion
	int k = 0, B;
	char option;
	
	while(k==0){
				
		//MENU DE ENTRADAS
		cout<<"ENTRADAS:\n"<<endl;
		cout<<"1-Palitos de Pizza\n2-Pan con ajo\n"<<endl;
		cout<<"Opcion: ";cin>>option;
		
		if(option == '1' || option == '2'){ //si la opcion esta en el menu entra al if
			
			if(option == '1'){ //si la opcion fue 1 la funcion retorna 3
				B = 3;
				k = 1; //para salirse del ciclo se modifica el valor de k
			}
			else{
				B = 4; //si fue 2 retorna el 4
				k = 1; 
			}
			
		}
		system("cls");		
	}
	return B;
}

//funcion de menu de bebidas
int Drinks(){
	//variables de la funcion
	int k = 0, C;
	char option;
	
	while(k==0){
		
		//MENU DE BEBIDAS
		cout<<"BEBIDAS:\n"<<endl;
		cout<<"1-Gaseosa\n2-Te\n"<<endl;
		cout<<"Opcion: ";cin>>option;
		
		if(option == '1' || option == '2'){ //si es una de las opciones existentes entra al if
			
			if(option == '1'){ //si fue 1 se retornara el numero 5
				C = 5;
				k = 1; //para salirse del ciclo se modifica el valor de k
			}
			else{    //si opcion fue 2 se returnara el 6
				C = 6;
				k = 1;
			}
			
		}			
		system("cls");
	}
	return C;
}
