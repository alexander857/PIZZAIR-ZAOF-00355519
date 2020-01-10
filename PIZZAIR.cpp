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
	char password[]="pizza", key[5]; //contraseña para el menu principal
	int attempts = 3; 
	
	//pedimos la contraseña para ingresar
	cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
	cout<<"Ingrese la clave: ";cin>>key;
	
	//hay solo 3 intentos para ingresar la contraseña correcta
	while(attempts > 0){
		
		//se compara si la contraseña es correcta
		if(key == password){
			
			cout<<"correcto!"<<endl;
			
		}
		else{
			attempts--;
			if(attempts==0){ //para que se cierre el programa al instante que los intentos se lleguen a 0
				break;
			}
		}
		system("cls");
		cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
		cout<<"Ingrese la clave: ";cin>>key;
		
	}
	system("cls");
	if(attempts == 0){
		cout<<"ERROR DE ACCESO!!"<<endl;
	}
	
	return 0;
}
