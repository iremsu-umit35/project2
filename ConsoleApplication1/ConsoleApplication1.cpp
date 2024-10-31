#include <iostream>
#include <queue>
#include <list>
using namespace std;
/*
	Bu proje, bir hastane kayıt ve önceliklendirme sistemi simülasyonudur.
	Projenin amacı, hastaların kayıt işlemlerini yaparak onları muayene önceliklerine göre sıralamaktır.
	Yaşı yüksek olan veya engelli durumunda olan hastalar, daha yüksek öncelik puanları alır ve muayene sırasına buna göre yerleştirilir.

	Projede kullanılan ana sınıflar:
	- Insan: Hasta ve normal insanları temsil eden temel sınıf. Hasta sınıfı bu sınıftan türetilmiştir.
	- Hasta: Insan sınıfından türetilmiş olup, her hastaya bir hasta numarası ve öncelik puanı atar.
			  Engelli olup olmadığına ve yaşına göre bir öncelik puanı hesaplanır.
	- HastaKayit: Kayıt ve muayene sırasını yönetir. Hastaları sıraya ekler ve muayene sırasına göre çağırır.

	Özetle, hasta kayıtları yapılır ve öncelik sırasına göre muayene edilecek hastalar çağırılır.
	Yaşlı ve/veya engelli hastalar daha yüksek öncelik puanına sahip olup önce muayene edilirler.

	Örnek Kullanım:
	- Hasta kayıtları yapılır.
	- Hasta kayıt sırası ve muayene sırası görüntülenir.
	- Hasta çağırma fonksiyonu ile sıradaki hasta muayeneye alınır.
*/


class Insan {
	protected:
		string ad;
		int yas;
		bool engelliMi;	
	public:
		Insan(string ad, int yas, bool engelliMi = false) : ad(ad), yas(yas), engelliMi(engelliMi) { } 
		 void yazdir()const{
			 cout << "Ad: " << ad << endl
				 << "Yas: " << yas << endl
				 << "engellilik durumu: ";
			 if (engelliMi)
				 cout << "EVET";
			 else
				 cout << "HAYIR";
			 cout << endl;
			 
		 } 
};



class Hasta :public Insan {
	int hastaNo;
	int oncelikPuanı;
public:
		Hasta(int hastaNo, Insan& i) : hastaNo(hastaNo), Insan(i), oncelikPuanı(0) {
			oncelikPuanıHesapla();
		}
		Hasta(int hastaNo, string ad, int yas, bool engelliMi=false) : hastaNo(hastaNo), Insan(ad, yas, engelliMi),oncelikPuanı(0) {
			oncelikPuanıHesapla();
		}
		void oncelikPuanıHesapla() {
			if (engelliMi)
				oncelikPuanı += 30;
			if (yas < 65)
				oncelikPuanı += yas - 65;
		}
		bool operator<(const Hasta& h)const {
			return oncelikPuanı < h.oncelikPuanı;
		}
		void yazdir()const {
			cout << "hasta no : " << hastaNo << endl;
			Insan::yazdir();
			cout << "Oncelik Puanı : " << oncelikPuanı << endl;
		}
};


class HastaKayıt {
	list<Hasta> kayıtSirasi;
	priority_queue<Hasta> muayeneSirasi;
	public:
		void kayit(Insan& i) {
			Hasta hasta(kayıtSirasi.size() + 1, i);
			muayeneSirasi.push(hasta);
			kayıtSirasi.push_back(hasta);
		}
		void kayitSirasiYazdir() {
			if (kayıtSirasi.empty())
				cout << "kayıtlı hasta yok" << endl;
			else {
				list<Hasta>::iterator iter = kayıtSirasi.begin();
				while (iter != kayıtSirasi.end()) {
					Hasta hasta = *iter;
					hasta.yazdir();
					iter++;
					if (iter != kayıtSirasi.end())
						cout << endl;
				}

			}
		}
		void muayeneSirasiYazdir() {
			if (muayeneSirasi.empty())
				cout << "muayene bekleyen  hasta yok" << endl;
			else {
				priority_queue<Hasta>kuyruk = muayeneSirasi;
				while (!kuyruk.empty()) {
					Hasta hasta = kuyruk.top();
					hasta.yazdir();
					kuyruk.pop();
					if (!kuyruk.empty())
						cout << endl;


				}

			}
		}
		void hastaCagır() {
			if (muayeneSirasi.empty())
				cout << "muayene için bekleyen hasta yok" << endl;
			else {
				cout << "muayene çağırılan hasta bilgileri" << endl;
				Hasta hasta = muayeneSirasi.top();
				hasta.yazdir();
				muayeneSirasi.pop();
			}
			cout << endl;
		}

};




int main() {
	Insan insanlar[] = {
		Insan("arif",30),
		Insan("ahmet",35,1),
		Insan("mehmet",70),
		Insan("veli",75,1),
		Insan("ferdi",45),

	};
	HastaKayıt banko;
	banko.kayit(insanlar[0]);
	banko.kayit(insanlar[1]);
	banko.kayit(insanlar[2]);
	banko.kayit(insanlar[3]);
	banko.kayit(insanlar[4]);
	banko.kayitSirasiYazdir();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	banko.muayeneSirasiYazdir();
}
