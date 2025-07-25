#include <iostream>
#include <cstdlib>
#include <cmath>
#include <windows.h>
#include <unistd.h>

using namespace std;

class Terrain{
	private:
		int content; 
	public:
		Terrain(){}
		void set_content(int, int, int);
		void turn(int);
		int get_content();
		~Terrain(){}
};

void Terrain::turn(int type){
	if (content==0) {
		if (type==1) content=3;
		if (type==2) content=4;
		if (type==3) content=5;
		if (type==4) content=6;
		return;
	}
	if (type==0) content=0;
}

void Terrain::set_content(int reml, int remtr, int maxj){
	int randNum = (rand() % 3) + 1;							/*Line taken by https://stackoverflow.com/a/5891824*/
	content=0;
	if (maxj>0){
		if (randNum==2){
			if (reml>0) content=1;
		}
		if (randNum==3){
			if (remtr>0) content=2;
		}
	}
}

int Terrain::get_content(){
	return content;
}

class Beings{
	private:
		int posx;
		int posy;
	public:
		void set_posx(int);
		void set_posy(int);
		int get_posx();
		int get_posy();
};

void Beings::set_posx(int x){
	posx=x;
}

void Beings::set_posy(int y){
	posy=y;
}

int Beings::get_posx(){
	return posx;
}

int Beings::get_posy(){
	return posy;
}

class Monsters: public Beings{
	private:
		int MaxHP;
		int hp;
		int type; /*1 for Vampires, 2 for Werewolves*/
		int atk;
		int def;
		int alive; /*1 for alive, 0 for dead*/
		int meds;
	public:
		Monsters(){}
		void set_MaxHP();
		void set_hp();
		void set_atk();
		void set_def();
		void set_typeV();
		void set_typeW();
		void set_alive();
		void set_meds();
		int get_MaxHP();
		int get_hp();
		int get_atk();
		int get_def();
		int get_type();
		int get_alive();
		int get_meds();
		void DMGtaken(int );
		void HPrestore();
		void usemeds();
		void receivemeds();
		~Monsters(){}
};

void Monsters::set_MaxHP(){
	MaxHP=(rand() % 10) + 1;
}

void Monsters::set_hp(){
	hp=MaxHP;
}

void Monsters::set_atk(){
	atk=(rand() % 3) + 1;
}

void Monsters::set_def(){
	def=(rand() % 2) + 1;
}

void Monsters::set_typeV(){
	type=1;
}

void Monsters::set_typeW(){
	type=2;
}

void Monsters::set_alive(){
	alive=1;					
}

void Monsters::set_meds(){
	meds=(rand()%3);
}

int Monsters::get_MaxHP(){
	return MaxHP;
}

int Monsters::get_hp(){
	return hp;
}

int Monsters::get_atk(){
	return atk;
}

int Monsters::get_def(){
	return def;
}

int Monsters::get_type(){
	return type;
}

int Monsters::get_alive(){
	return alive;
}

int Monsters::get_meds(){
	return meds;
}

void Monsters::DMGtaken(int dmg){
	hp=hp-dmg+def;
	if (hp<=0) alive=0;
}

void Monsters::HPrestore(){
	if (alive==1) hp=MaxHP;
}

void Monsters::usemeds(){
	meds--;
}

void Monsters::receivemeds(){
	hp++;
}

class Vampires: public Monsters{
	public:
		void move(int);
};

void Vampires::move(int dir){
	int x=get_posx();
	int y=get_posy();
	if (dir==1){
		x--;
		y--;
	}
	if (dir==2){
		x--;
	}
	if (dir==3){
		x--;
		y++;
	}
	if (dir==4){
		y--;
	}
	if (dir==5){
		y++;
	}
	if (dir==6){
		x++;
		y--;
	}
	if (dir==7){
		x++;
	}
	if (dir==8){
		x++;
		y++;
	}
	set_posx(x);
	set_posy(y);
}

class Werewolves: public Monsters{
	public:
		void move(int);
};

void Werewolves::move(int dir){
	int x=get_posx();
	int y=get_posy();
	if (dir==1) {
		x--;
	}
	if (dir==2) {
		y++;
	}
	if (dir==3) {
		x++;
	}
	if (dir==4) {
		y--;
	}
	set_posx(x);
	set_posy(y);
}

class Avatar: public Beings{
	private:
		int potions=1;
		int type=3;
	public:
		Avatar(){}
		int get_potions();
		void use_potion();
		int take_potion();
		int get_type();
		~Avatar(){}
};

void Avatar::use_potion(){
	potions--;
}

int Avatar::get_potions(){
	return potions;
}

int Avatar::take_potion(){
	potions++;
}

int Avatar::get_type(){
	return type;
}

class XPotion: public Beings{
	private:
		int type=4;
	public:
		XPotion(){}
		int get_type();
		~XPotion(){}
};

int XPotion::get_type(){
	return type;
}

int main(){
	int n, i, m, j, i1, j1, rem, reml, remtr, maxj, vam, wer, found, blanktype=0,dayc=1, pass=0, turn, f, flag, tcomp, dir, fx, fy, amount, h;
	char day='D';
	int randNum1,randNum2;
	cin >> n;
	cin >> m;					
	Terrain Tile[n][m];
	rem=sqrt(n*m)-1;
	reml=rem/2;
	remtr=rem-reml;
	for (i=0;i<n;i++){
		maxj=2;
		for (j=0;j<m;j++){
			Tile[i][j].set_content(reml, remtr, maxj);
			if (Tile[i][j].get_content()==1){
				maxj--;
				reml--;
			}
			if (Tile[i][j].get_content()==2){
				maxj--;
				remtr--;
			}
		}
	}
	vam=n*m/15;
	wer=n*m/15;
	Vampires Vamps[vam];
	Werewolves Wolves[wer];
	for (i=0;i<vam;i++){
		Vamps[i].set_alive();
		Wolves[i].set_alive();
		Vamps[i].set_MaxHP();
		Wolves[i].set_MaxHP();
		Vamps[i].set_hp();
		Wolves[i].set_hp();
		Vamps[i].set_atk();
		Wolves[i].set_atk();
		Vamps[i].set_def();
		Wolves[i].set_def();
		Vamps[i].set_typeV();
		Wolves[i].set_typeW();
		Vamps[i].set_meds();
		Wolves[i].set_meds();
		found=0;
		while(found==0){
			randNum1=(rand() % n);
			randNum2=(rand() % m);
			if (Tile[randNum1][randNum2].get_content()==0 ){
				found=1;
				Tile[randNum1][randNum2].turn(Vamps[i].get_type());
				Vamps[i].set_posx(randNum1);
				Vamps[i].set_posy(randNum2);
			}
		}
		found=0;
		while(found==0){
			randNum1=(rand() % n);
			randNum2=(rand() % m);
			if (Tile[randNum1][randNum2].get_content()==0 ){
				found=1;
				Tile[randNum1][randNum2].turn(Wolves[i].get_type());
				Wolves[i].set_posx(randNum1);
				Wolves[i].set_posy(randNum2);
			}
		}
	}
	Avatar Alucard;
	found=0;
	while(found==0){
		randNum1=(rand() % n);
		randNum2=(rand() % m);
		if (Tile[randNum1][randNum2].get_content()==0 ){
			found=1;
			Tile[randNum1][randNum2].turn(Alucard.get_type());
			Alucard.set_posx(randNum1);
			Alucard.set_posy(randNum2);
		}
	}
	XPotion Potion;
	found=0;
	while(found==0){
		randNum1=(rand() % n);
		randNum2=(rand() % m);
		if (Tile[randNum1][randNum2].get_content()==0 ){
			found=1;
			Tile[randNum1][randNum2].turn(Potion.get_type());
			Potion.set_posx(randNum1);
			Potion.set_posy(randNum2);
		}
	}
	for (i=0;i<n;i++){
		for (j=0;j<m;j++){
			if (Tile[i][j].get_content()==0) cout<<".";
			if (Tile[i][j].get_content()==1) cout<<"L";
			if (Tile[i][j].get_content()==2) cout<<"T";
			if (Tile[i][j].get_content()==3) cout<<"V";
			if (Tile[i][j].get_content()==4) cout<<"W";
			if (Tile[i][j].get_content()==5) cout<<"A";
			if (Tile[i][j].get_content()==6) cout<<"P";
			if (j==m-1) cout<<endl;
		}
	}
	int game_on=1;
	while (game_on==1){
		system("cls");
		for (i=0;i<n;i++){
			for (j=0;j<m;j++){
				if (Tile[i][j].get_content()==0) cout<<".";
				if (Tile[i][j].get_content()==1) cout<<"L";
				if (Tile[i][j].get_content()==2) cout<<"T";
				if (Tile[i][j].get_content()==3) cout<<"V";
				if (Tile[i][j].get_content()==4) cout<<"W";
				if (Tile[i][j].get_content()==5) cout<<"A";
				if (Tile[i][j].get_content()==6) cout<<"P";
				if (j==m-1) cout<<endl;
			}
		}
		flag=0;
		for (i=0; i<vam; i++){
			if (Vamps[i].get_alive()==1) flag=1;
		}
		if (flag==0){
			system("cls");
			cout<<"Werewolves WIN"<<endl;
			game_on=0;
		}
		flag=0;
		for (i=0; i<wer; i++){
			if (Wolves[i].get_alive()==1) flag=1;
		}
		if (flag==0){
			system("cls");
			cout<<"Vampires WIN"<<endl;
			game_on=0;
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			game_on=0;
		}
		if (GetAsyncKeyState(VK_UP)){
			i=Alucard.get_posx();
			j=Alucard.get_posy();
			if (i>0){
				if (Tile[i-1][j].get_content()==0){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i-1][j].turn(Alucard.get_type());
					Alucard.set_posx(i-1);
					Alucard.set_posy(j);
				}
				if (Tile[i-1][j].get_content()==6){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i-1][j].turn(Alucard.get_type());
					Alucard.set_posx(i-1);
					Alucard.set_posy(j);
					Alucard.take_potion();
				}
			}
		}
		if (GetAsyncKeyState(VK_LEFT)){
			i=Alucard.get_posx();
			j=Alucard.get_posy();
			if (j>0){
				if (Tile[i][j-1].get_content()==0){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i][j-1].turn(Alucard.get_type());
					Alucard.set_posx(i);
					Alucard.set_posy(j-1);
				}
				if (Tile[i][j-1].get_content()==6){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i][j-1].turn(Alucard.get_type());
					Alucard.set_posx(i);
					Alucard.set_posy(j-1);
					Alucard.take_potion();
				}
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)){
			i=Alucard.get_posx();
			j=Alucard.get_posy();
			if (j+1<m){
				if (Tile[i][j+1].get_content()==0){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i][j+1].turn(Alucard.get_type());
					Alucard.set_posx(i);
					Alucard.set_posy(j+1);
				}
				if (Tile[i][j+1].get_content()==6){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i][j+1].turn(Alucard.get_type());
					Alucard.set_posx(i);
					Alucard.set_posy(j+1);
					Alucard.take_potion();
				}
			}
		}
		if (GetAsyncKeyState(VK_DOWN)){
			i=Alucard.get_posx();
			j=Alucard.get_posy();
			if (i+1<n){
				if (Tile[i+1][j].get_content()==0){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i+1][j].turn(Alucard.get_type());
					Alucard.set_posx(i+1);
					Alucard.set_posy(j);
				}
				if (Tile[i+1][j].get_content()==6){
					blanktype=0;
					Tile[i][j].turn(blanktype);
					Tile[i+1][j].turn(Alucard.get_type());
					Alucard.set_posx(i+1);
					Alucard.set_posy(j);
					Alucard.take_potion();
				}
			}
		}
		for (i=0;i<wer;i++){    													
			if (Wolves[i].get_alive()==1){
				tcomp=0;
				turn=rand()%2;
				flag=0;
				for (j=0;j<=wer;j++){
					i1=Wolves[i].get_posx()-Wolves[j].get_posx();
					j1=Wolves[i].get_posy()-Wolves[j].get_posy();
					if (((i1==-1 && j1==-1)||(i1==-1 && j1==0)||(i1==-1 && j1==1)||(i1==0 && j1==-1)||(i1==0 && j1==1)||(i1==1 && j1==-1)||(i1==1 && j1==0)||(i1==1 && j1==1))&Vamps[j].get_alive()==1){
						if (Wolves[j].get_hp()!=Wolves[j].get_MaxHP()){
							if (Wolves[i].get_meds()>0){
								if (turn==1){
									tcomp=1;
									Wolves[i].usemeds();
									Wolves[j].receivemeds();
								}
							}
						}
					}
				}
				for (j=0;j<=vam;j++){
					i1=Wolves[i].get_posx()-Vamps[j].get_posx();
					j1=Wolves[i].get_posy()-Vamps[j].get_posy();
					if (((i1==-1 && j1==-1)||(i1==-1 && j1==0)||(i1==-1 && j1==1)||(i1==0 && j1==-1)||(i1==0 && j1==1)||(i1==1 && j1==-1)||(i1==1 && j1==0)||(i1==1 && j1==1))&Vamps[j].get_alive()==1){
						fx=Vamps[j].get_posx();
						fy=Vamps[j].get_posy();
						flag=1;
						f=j;
					}
				}
				if (turn==1 & flag==1){
					if (Wolves[i].get_atk()>=Vamps[f].get_atk()){
						Vamps[f].DMGtaken(Wolves[i].get_atk());
						tcomp=1;
					}
					i1=fx-Wolves[i].get_posx();
					j1=fy-Wolves[i].get_posy();
					if (Wolves[i].get_atk()<Vamps[f].get_atk()){
						if ((i1+j1==0 && i1>j1)||(i1+j1==1 && i1>j1)||i1+j1==2){
							if (Wolves[i].get_posx()>0){
								if (Tile[Wolves[i].get_posx()-1][Wolves[i].get_posy()].get_content()==0){
									tcomp=1;
									dir=1;
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(blanktype);
									Wolves[i].move(dir);
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(Wolves[i].get_type());
								}
							}
						}
						if ((i1+j1==-2||(i1+j1==-1 && i1>j1)||(i1+j1==0 &&i1>j1)) && tcomp==0){
							if (Wolves[i].get_posy()<m-1){
								if (Tile[Wolves[i].get_posx()][Wolves[i].get_posy()+1].get_content()==0){
									tcomp=1;
									dir=2;
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(blanktype);
									Wolves[i].move(dir);
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(Wolves[i].get_type());
								}
							}
						}
						if ((i1+j1==-2||(i1+j1==-1 && i1<j1)||(i1+j1==0 &&i1<j1)) && tcomp==0){
							if (Wolves[i].get_posx()<n-1){
								if (Tile[Wolves[i].get_posx()+1][Wolves[i].get_posy()].get_content()==0){
									tcomp=1;
									dir=3;
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(blanktype);
									Wolves[i].move(dir);
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(Wolves[i].get_type());
								}
							}
						}
						if ((i1+j1==2||(i1+j1==1 && i1<j1)||(i1+j1==0 &&i1<j1)) && tcomp==0){
							if (Wolves[i].get_posy()>0){
								if (Tile[Wolves[i].get_posx()][Wolves[i].get_posy()-1].get_content()==0){
									tcomp=1;
									dir=4;
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(blanktype);
									Wolves[i].move(dir);
									Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(Wolves[i].get_type());
								}
							}
						}
					}
				}
				if (turn==1 && flag==0 && tcomp==0){
					flag=0;
					f=0;
					while(flag==0&&f<=16){
						dir=rand()%4+1;
						if (Wolves[i].get_posx()>0){
							if (dir==1 && Tile[Wolves[i].get_posx()-1][Wolves[i].get_posy()].get_content()==0){
								flag=1;
							}
						}
						if (Wolves[i].get_posy()<m-1){
							if (dir==2 && Tile[Wolves[i].get_posx()][Wolves[i].get_posy()+1].get_content()==0){
								flag=1;
							}
						}
						if (Wolves[i].get_posx()<n-1){
							if (dir==3 && Tile[Wolves[i].get_posx()+1][Wolves[i].get_posy()].get_content()==0){
								flag=1;
							}
						}
						if (Wolves[i].get_posy()>0){
							if (dir==4 && Tile[Wolves[i].get_posx()][Wolves[i].get_posy()-1].get_content()==0){
								flag=1;
							}
						}
						f++;
					}
					if (flag==1){
						Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(blanktype);
						Wolves[i].move(dir);
						Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(Wolves[i].get_type());
					}
				}	
			}
		}
		for (i=0;i<vam;i++){    													
			if (Vamps[i].get_alive()==1){
				tcomp=0;
				turn=rand()%2;
				flag=0;
				for (j=0;j<=vam;j++){
					i1=Vamps[i].get_posx()-Vamps[j].get_posx();
					j1=Vamps[i].get_posy()-Vamps[j].get_posy();
					if (((i1==-1 && j1==-1)||(i1==-1 && j1==0)||(i1==-1 && j1==1)||(i1==0 && j1==-1)||(i1==0 && j1==1)||(i1==1 && j1==-1)||(i1==1 && j1==0)||(i1==1 && j1==1))&Wolves[j].get_alive()==1){
						if (Vamps[j].get_hp()!=Vamps[j].get_MaxHP()){
							if (Vamps[i].get_meds()>0){
								if (turn==1){
									tcomp=1;
									Vamps[i].usemeds();
									Vamps[j].receivemeds();
								}
							}
						}
					}
				}
				for (j=0;j<=wer;j++){
					i1=Vamps[i].get_posx()-Wolves[j].get_posx();
					j1=Vamps[i].get_posy()-Wolves[j].get_posy();
					if (((i1==-1 && j1==-1)||(i1==-1 && j1==0)||(i1==-1 && j1==1)||(i1==0 && j1==-1)||(i1==0 && j1==1)||(i1==1 && j1==-1)||(i1==1 && j1==0)||(i1==1 && j1==1))&Wolves[j].get_alive()==1){
						fx=Wolves[j].get_posx();
						fy=Wolves[j].get_posy();
						flag=1;
						f=j;
					}
				}
				if (turn==1 & flag==1){
					if (Vamps[i].get_atk()>=Wolves[f].get_atk()){
						Wolves[f].DMGtaken(Vamps[i].get_atk());
						tcomp=1;
					}
					i1=fx-Vamps[i].get_posx();
					j1=fy-Vamps[i].get_posy();
					if (Vamps[i].get_atk()<Wolves[f].get_atk()){
						if ((i1+j1==0 && i1!=j1)||i1+j1==1||i1+j1==2){
							if (Vamps[i].get_posx()>0 && Vamps[i].get_posy()>0 && tcomp==0){
								if (Tile[Vamps[i].get_posx()-1][Vamps[i].get_posy()-1].get_content()==0){
									tcomp=1;
									dir=1;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
						if ((i1+j1==0 && i1>j1)||(i1+j1==1 && i1>j1)||i1+j1==2){
							if (Vamps[i].get_posx()>0 && tcomp==0){
								if (Tile[Vamps[i].get_posx()-1][Vamps[i].get_posy()].get_content()==0){
									tcomp=1;
									dir=2;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
						if (i1+j1==-2||(i1+j1==-1 && i1>j1)||(i1+j1==0 && i1>j1)||(i1+j1==1 && i1>j1)||i1+j1==2){
							if (Vamps[i].get_posx()>0 && Vamps[i].get_posy()<m-1 && tcomp==0){
								if (Tile[Vamps[i].get_posx()-1][Vamps[i].get_posy()+1].get_content()==0){
									tcomp=1;
									dir=3;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
						if ((i1+j1==2||(i1+j1==1 && i1<j1)||(i1+j1==0 &&i1<j1)) && tcomp==0){
							if (Vamps[i].get_posy()>0){
								if (Tile[Vamps[i].get_posx()][Vamps[i].get_posy()-1].get_content()==0){
									tcomp=1;
									dir=4;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
						if ((i1+j1==-2||(i1+j1==-1 && i1>j1)||(i1+j1==0 &&i1>j1)) && tcomp==0){
							if (Vamps[i].get_posy()<m-1){
								if (Tile[Vamps[i].get_posx()][Vamps[i].get_posy()+1].get_content()==0){
									tcomp=1;
									dir=5;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
						if ((i1+j1==-2||(i1+j1==-1 && i1<j1)||(i1+j1==0 &&i1<j1)||(i1+j1==1 && i1>j1)||i1+j1==2) && tcomp==0){
							if (Vamps[i].get_posx()<n-1&&Vamps[i].get_posy()>0){
								if (Tile[Vamps[i].get_posx()+1][Vamps[i].get_posy()-1].get_content()==0){
									tcomp=1;
									dir=6;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
						if ((i1+j1==-2||(i1+j1==-1 && i1<j1)||(i1+j1==0 &&i1<j1)) && tcomp==0){
							if (Vamps[i].get_posx()<n-1){
								if (Tile[Vamps[i].get_posx()+1][Vamps[i].get_posy()].get_content()==0){
									tcomp=1;
									dir=7;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
						if ((i1+j1==-2||i1+j1==-1||(i1+j1==0 &&i1!=j1)) && tcomp==0){
							if (Vamps[i].get_posx()<n-1&&Vamps[i].get_posy()<m-1){
								if (Tile[Vamps[i].get_posx()+1][Vamps[i].get_posy()+1].get_content()==0){
									tcomp=1;
									dir=8;
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
									Vamps[i].move(dir);
									Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
								}
							}
						}
					}
				}
				if (turn==1 && flag==0 && tcomp==0){
					flag=0;
					f=0;
					while(flag==0&&f<=16){
						dir=rand()%8+1;
						if (Vamps[i].get_posx()>0 && Vamps[i].get_posy()>0){
							if (dir==1 && Tile[Vamps[i].get_posx()-1][Vamps[i].get_posy()-1].get_content()==0){
								flag=1;
							}
						}
						if (Vamps[i].get_posx()>0){
							if (dir==2 && Tile[Vamps[i].get_posx()-1][Vamps[i].get_posy()].get_content()==0){
								flag=1;
							}
						}
						if (Vamps[i].get_posx()>0 && Vamps[i].get_posy()<m-1){
							if (dir==3 && Tile[Vamps[i].get_posx()-1][Vamps[i].get_posy()+1].get_content()==0){
								flag=1;
							}
						}
						if (Vamps[i].get_posy()>0){
							if (dir==4 && Tile[Vamps[i].get_posx()][Vamps[i].get_posy()-1].get_content()==0){
								flag=1;
							}
						}
						if (Vamps[i].get_posy()<m-1){
							if (dir==5 && Tile[Vamps[i].get_posx()][Vamps[i].get_posy()+1].get_content()==0){
								flag=1;
							}
						}
						if (Vamps[i].get_posx()<n-1 && Vamps[i].get_posy()>0){
							if (dir==6 && Tile[Vamps[i].get_posx()+1][Vamps[i].get_posy()-1].get_content()==0){
								flag=1;
							}
						}
						if (Vamps[i].get_posx()<n-1){
							if (dir==7 && Tile[Vamps[i].get_posx()+1][Vamps[i].get_posy()].get_content()==0){
								flag=1;
							}
						}
						if (Vamps[i].get_posx()<n-1 && Vamps[i].get_posy()<m-1){
							if (dir==8 && Tile[Vamps[i].get_posx()+1][Vamps[i].get_posy()+1].get_content()==0){
								flag=1;
							}
						}
						f++;
					}
					if (flag==1){
						Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
						Vamps[i].move(dir);
						Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(Vamps[i].get_type());
					}
				}	
			}
		}
		for (i=0;i<wer;i++){
			if (Wolves[i].get_alive()==0) Tile[Wolves[i].get_posx()][Wolves[i].get_posy()].turn(blanktype);
		}
		for (i=0;i<wer;i++){
			if (Vamps[i].get_alive()==0) Tile[Vamps[i].get_posx()][Vamps[i].get_posy()].turn(blanktype);
		}
		if (dayc%10==0){
			if (day=='D') {
				day='N';
				pass=1;
			}
			if (pass==0){
				day='D';
			}
			pass=0;
		}
		if (GetAsyncKeyState(VK_SPACE)){
			if (Alucard.get_potions()>0){
				if (day=='D'){
					for (j=0;j<vam;j++){
						if (Vamps[i].get_alive()==1){
							Vamps[i].HPrestore();
						}
					}
					Alucard.use_potion();
				}
				if (day=='N'){
					for (i=0;i<wer;i++){
						if (Wolves[i].get_alive()==1){
							Wolves[i].HPrestore();
						}
					}
					Alucard.use_potion();
				}
			}
		}
		if (GetAsyncKeyState(VK_BACK)){
			amount=0;
			cout<<"Potions:"<<Alucard.get_potions()<<endl;
			for (i=0;i<=vam;i++){
				if (Vamps[i].get_alive()==1) amount++;
			}
			cout<<"Vampires alive:"<<amount<<endl;
			amount=0;
			for (i=0;i<=wer;i++){
				if (Wolves[i].get_alive()==1)amount++;
			}
			cout<<"Werewolves alive:"<<amount<<endl;
			system("pause");
		}
		dayc++;
		cout << day<<endl;
		sleep(1);
	}
}
