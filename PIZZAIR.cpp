#include<iostream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

using namespace std;

//prototipos de las funciones


int main(){
	//declaracion de variables
	char password[]="pizza", key[5]; //contrase?a para el menu principal 
	int k = 0; 
	
	//pedimos la contrase?a para ingresar
	cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
	cout<<"Ingrese la clave: ";cin>>key;
	
	//hay solo 3 intentos para ingresar la contrase?a correcta
	while(k==0){
		
		//se compara si la contrase?a es correcta
		if(strcmp(password,key) == 0){ //compara las dos palabras: password y key 
			cout<<"Correcto"<<endl;
			break;
		}
		
		else{     //si no son iguaes las palabras, le sigue pidiendo que ingrese la clave hasta que ingrese la correcta
			
			system("cls");
			cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
			cout<<"Ingrese la clave: ";cin>>key;
			
		}	
						
	}
	
	return 0;
}
