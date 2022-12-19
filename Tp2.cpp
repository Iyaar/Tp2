#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;



// Les classes

class Personne {
    public:
        int id;
        string nom;
        int zoneGeo;
        string formatForFile() {return to_string(id) + " " + nom + " " + to_string(zoneGeo);}
        string formatForUser(const string &temp) {return temp + "\n id:" + to_string(id) + " name:" + nom + " zone:" + to_string(zoneGeo);}
};

class Recommande {
    public:
        int idR;
        string type;
        int idF;
        int idD;
        Recommande(int x, string s, int f, int d) {idR = x; type = s; idF = f; idD = d;}
        string formatForFile() {return to_string(idR) + " " + type + " " + to_string(idF) + " " + to_string(idD);}
        string formatForUser() {return "RECOMMANDE\nid:" + to_string(idR) + " type:" + type + " idFacteur:" + to_string(idF) + " idD:" + to_string(idD);}
};

class Facteur : public Personne {
    public:
        Facteur(int idF, string nomF, int zoneGF) {id = idF; nom = nomF; zoneGeo = zoneGF;}
        
};

class Habitant : public Personne {
    public:
        Habitant(int idH, string nomH, int zoneGH) {id = idH; nom = nomH; zoneGeo = zoneGH;}
};

//Fonction Chiffrement
//Demander la matrice cle de l'utilisateur
float en[3][1], de[3][1], a[3][3], b[3][3], msg[3][1], m[3][3];
void getKeyMatrix() { 

   int i, j;
   char mes[3];
   cout<<"Entrer une matrice 3*3 pour la cle (doit avoir un inverse):\n";
   for(i = 0; i < 3; i++)
   for(j = 0; j < 3; j++) {
      cin>>a[i][j];
      m[i][j] = a[i][j];
   }
 
}
void encrypt() { //Crypter le message
   int i, j, k;
   
   for(i = 0; i < 3; i++)
   for(j = 0; j < 1; j++)
   for(k = 0; k < 3; k++)
   en[i][j] = en[i][j] + a[i][k] * msg[k][j];
   cout<<"\nle message crypte est";
   for(i = 0; i < 3; i++)
   cout<<(char)(fmod(en[i][0], 26) + 65); 
}
void inversematrix() {// trouver l''inverse de la matrice cle
   int i, j, k;
   float p, q;
   for(i = 0; i < 3; i++)
   for(j = 0; j < 3; j++) {
      if(i == j)
         b[i][j]=1;
      else
         b[i][j]=0;
   }
   for(k = 0; k < 3; k++) {
      for(i = 0; i < 3; i++) {
         p = m[i][k];
         q = m[k][k];
         for(j = 0; j < 3; j++) {
            if(i != k) {
               m[i][j] = m[i][j]*q - p*m[k][j];
               b[i][j] = b[i][j]*q - p*b[k][j];
            }
         }
      }
   }
   for(i = 0; i < 3; i++)
   for(j = 0; j < 3; j++)
   b[i][j] = b[i][j] / m[i][i];
   cout<<"\n\nInverse Matrix is:\n";
   for(i = 0; i < 3; i++) {
      for(j = 0; j < 3; j++)
      cout<<b[i][j]<<" ";
      cout<<"\n";
   }
}
void decrypt() { //decrypter le message
   int i, j, k;
   inversematrix();
   for(i = 0; i < 3; i++)
   for(j = 0; j < 1; j++)
   for(k = 0; k < 3; k++)
   de[i][j] = de[i][j] + b[i][k] * en[k][j];
   cout<<"\nDecrypted string is: ";
   for(i = 0; i < 3; i++)
   cout<<(char)(fmod(de[i][0], 26) + 65); 
}




int main() {
    string filename, line;


//ouvrir fichier Facteur 
  ofstream myfileF;
  myfileF.open ("Facteur.txt");

//Lire le fichier Facteur
void readF(vector<Facteur>&f,vector<string> rkb,vector<string> rk) {
     fstream myfileF; 
     myfilef.open("Facteur.txt");
     string s,nomF,ZoneGF;
     int j=0;
      while(getline( myfileF, s )) {
            idF="";
            ZoneGF="";
            int i=0;
            string nzf="";
            while ((i<s.size())&&(s[i]!=' '))
            {   
                
                name+=s[i];
                i++;
            }
            for (int k =i+1; k <s.size(); k++)
            {
                nzf+=s[k];
            }
            name=decrypt(name,rkb,rk);
            nzf=decrypt(nzf,rkb,rk);
            f[i].setNomf(name);
            f[i].setZonef(stoi(nzf));//de string a int
            j++;
        }
    myfilef.close();    
}
  
//ajouter au fichier Facteur
    if (myfileF.is_open()){
        myfileF<<" "<< endl;
        myfileF.close();
    }

//ouvrir fichier Habitant
  ofstream myfileH;
  myfileH.open ("Habitant.txt");

//Lire le fichier Habitant
void readH(vector<Habitant>&h,vector<string> rkb,vector<string> rk) {
     fstream myfileH; 
     myfileH.open("Habitant.txt");
     string s,name,idZ;
     int j=0;
      while(getline( datah, s )) {
            name=" ";
            idZ="";
            int i=0;
            string nzh="";
            while ((i<s.size())&&(s[i]!=' '))
            {   
                name+=s[i];
                i++;
            }
            for (int k =i+1; k <s.size(); k++)
            {
                nzh+=s[k];
            }
            name=decrypt(name,rkb,rk);
            nzh=decrypt(nzh,rkb,rk);
            h[i].setNomh(name);
            h[i].setZoneh(stoi(nzh));//stoi function convert from string to int
            j++;
        }
    datah.close();
}

//ajouter au fichier Habitant
    if (myfileH.is_open()){
        myfileH <<" "<< endl;
        myfileH.close();
    }


//ouvrir fichier Recommande
  ofstream myfileR;
  myfileR.open ("Recommande.txt");

//ajouter au fichier Recommande
    if (myfileR.is_open()){
        myfileR<<" "<< endl;
        myfileR.close();
    }

//Lire le fichier Recommande
void readR(vector<Recommande>&r,vector<string> rkb,vector<string> rk){
     fstream myfileR; 
     myfileR.open("Recommande.txt");
     string s,numf,numh,type;
     int j=0;
      while(getline( myfileR, s )) {
            idF="";
            idH="";
            type="";
            int i=0;
            while ((i<s.size())&&(s[i]!=' '))
            {   
                idF+=s[i];
                 i++;
            }
            int k =i+1;
            while ((k<s.size())&&(s[k]!=' '))
            {
                idH+=s[k];
                k++;
            }
            for (int t = 0; t < s.size(); t++)
            {
                type+=s[i];
            }
            //decrytpt line
            numf=decrypt(numf,rkb,rk);
            numh=decrypt(numh,rkb,rk);
            type=decrypt(type,rkb,rk);
            r[i].setNumf(stoi(numf));
            r[i].setNumh(stoi(numh));
            r[i].setType(type);
            j++;
        }
    myfileR.close();

}

return 0;
}
  






