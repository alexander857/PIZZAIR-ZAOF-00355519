#include<iostream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

using namespace std;

//registros

//direccion del cliente
struct CustomerAddress{

	int HouseNumber;
	string Suburb;
	string Municipality;
	string State;

};

//ordenes a domicilio
struct HomeOrders{
	
	string name;
	HouseNumber Address;
	int phone;
	string MainDish;
	string StarterPlate;
	string drink;
	double amount;
	string PaymentType;
	
};

//pedidos a restaurante
struct CustomInRestaurant{
	
	string name;
	int PeoplePerTable;
	string MainDish;
	string StarterPlate;
	string drink;
	double amount;
	string PaymentType;
	
};



//PROTOTIPOS DE LAS FUNCIONES
//funcion de menu principal
char PizzaMenu();

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
			option = PizzaMenu(); //se llama la funcion del menu principal si la contrase��a es correcta
			system("cls");
			
			//condiciones segun lo que se seleccione en el menu principal
			if(option == '1'){
				
			
				
			}
			else if(option == '2'){
				
				
				
			}
			else if(option == '3'){
				
				
				
			}
			else if(option == '4'){
				
				
				
			}
			else if(option == '5'){
				
			

			}
			else if(option == '6'){
				
				break;  //al seleccionar la opcion salir se cierra el programa
				
			}					
		
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
	cout<<"1-Agregar 1 pedido a domicilio\n2-Agregar 1 encargo en restaurante\n3-Ver pedidos a domicilio\n"
	"4-Ver encargos en restaurante\n5-Ver total de ventas\n6-Salir\n"<<endl;
	
	//se pide una opcion a seleccionar
	cout<<"Opcion: ";cin>>option;
	
	return option;
}