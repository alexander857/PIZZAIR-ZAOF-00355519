#include<iostream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

using namespace std;

//prototipos de las funciones
char PizzaMenu();
void FoodMenu();

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

//funcion de los menu de comida
void FoodMenu(){
	//variables declaradas
	int k = 0;
	char optionP, optionE, optionB;
	
	//while donde se muestra el menu de platos principales
	while(k==0){
		
		//MENU DE PLATOS PRINCIPALES			
		cout<<"PLATO PRINCIPAL:\n"<<endl;
		cout<<"1-Pizza\n2-Ensalada\n3-Pasta\n"<<endl;
		cout<<"Opcion: ";cin>>optionP;
		system("cls");
		
		if(optionP == '1' || optionP == '2' || optionP == '3'){ //si es una de las opciones pasa al siquiente menu
			
			while(k==0){
				
				//ENTRADAS
				cout<<"ENTRADAS:\n"<<endl;
				cout<<"1-Palitos de Pizza\n2-Pan con ajo\n"<<endl;
				cout<<"Opcion: ";cin>>optionE;
				system("cls");
				
				if(optionE == '1' || optionE == '2'){ //si selecciona una de las opciones existentes pasa al siguiente menu y ultimo
					
					//BEBIDAS
					cout<<"BEBIDAS:\n"<<endl;
					cout<<"1-Gaseosa\n2-Te\n"<<endl;
					cout<<"Opcion: ";cin>>optionB;
					k=1;
					
				}
				
			}
						
		}		
		
	}
		
}

