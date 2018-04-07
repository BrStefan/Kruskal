#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct muchie_struct
{
	int nod1,nod2,cost;
};

//citirea nr de noduri+muchii si a grafului
void citire_date(vector <muchie_struct> &v , int& n , int& m)
{
	muchie_struct aux;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",&aux.nod1,&aux.nod2,&aux.cost);
		v.push_back(aux);
	}
}

//functia de comparare pt sortarea crescatoare dupa cost
bool cmp(muchie_struct a,muchie_struct b)
{
	return a.cost<=b.cost;
}

//Returneaza vf arborelui + compresie de cale
int Reprezentant(int nod,int t[])
{
	if(t[nod]==0)return nod;
	t[nod]=Reprezentant(t[nod],t);
	return t[nod];
}

//Reuniunea a 2 arbori
void Reuneste(int u,int v, int tata[],int h[])
{
	int ru,rv;
	ru=Reprezentant(u,tata);
	rv=Reprezentant(v,tata);
	if(h[ru]>h[rv])tata[rv]=u;
	else
	{
		tata[ru]=v;
		if(h[ru]==h[rv])h[rv]++;
	}
}

//aplicarea algortimului Kruskal
void Kruskal(vector <muchie_struct> v,int n,int m)
{
	unsigned int cnt,r1,r2;
	int *tata,*inaltime;

	tata=new int[n+1];
	inaltime=new int[n+1];

	vector <muchie_struct> aux;
	muchie_struct aux2;

	for(int i=0;i<=n;i++)tata[i]=inaltime[i]=0;
	for(unsigned int i=0;i<m;i++)
	{
		r1=Reprezentant(v[i].nod1,tata);
		r2=Reprezentant(v[i].nod2,tata);
		if(r1!=r2)
		{
			Reuneste(v[i].nod1,v[i].nod2,tata,inaltime);
			cnt++;
			aux2.nod1=v[i].nod1;
			aux2.nod2=v[i].nod2;
			aux2.cost=v[i].cost;
			aux.push_back(aux2);
		}
		if(cnt==n-1)break;
	}
	for(int i=0;i<n-1;i++)
		printf("Muchia %d: %d-%d de cost %d\n",i+1,aux[i].nod1,aux[i].nod2,aux[i].cost);
}
int main()
{
	//varibile
	int nr_noduri,nr_muchii;
	vector<muchie_struct> muchie;

	//initializare citire
	freopen("date.in","r",stdin);
	freopen("date.out","w",stdout);

	//citirea datelor
	citire_date(muchie,nr_noduri,nr_muchii);

	//sortarea muchiilor in ordine crescatoare
	sort(&muchie[0],&muchie[nr_muchii],cmp);

	//aplicare algoritm
	Kruskal(muchie,nr_noduri,nr_muchii);

}