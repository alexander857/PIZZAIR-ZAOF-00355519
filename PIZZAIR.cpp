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
	string password="pizza", key; //contrase?a para el menu principal 
	int k = 0; 
	bool clave = false; //verificar si la contraseña es correcta
	
	//pedimos la contrase?a para ingresar
	cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
	cout<<"Ingrese la clave: ";cin>>key;
	
	//hay solo 3 intentos para ingresar la contrase?a correcta
	while(k==0){
		
		//se compara si la contrase?a es correcta
		for(int i=0;i<key.length();i++){
			
			if(key[i] == password[i]){
				
				clave = true;  //si cada letra de la clave es igual a la contraseña clave pasa a true
				
			}

		}
		
		if(clave == true){         //si al final del for clave es verdadera es porque toda la clave es igual a la contraseña, por lo tanto ingresa
			cout<<"Correcto"<<endl;
			k = 1; //variable pasa a 1 para que salga del while
		}
		else{     //si la clave no fue igual, clave se mantiene en false y le seguira pidiendo la clave hasta que ingrese la correcta
			
			system("cls");
			cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
			cout<<"Ingrese la clave: ";cin>>key;
			
		}	
						
	}
	
	return 0;
}