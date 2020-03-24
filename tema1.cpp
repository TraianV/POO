#include<iostream>
using namespace std;
class vector
{
    int *v, n;

public:
    friend class vectori_de_vectori;

    vector(int n,int *x)///initializare cu numere
    {
        delete []v;
        this->n=n;
        v=new int [n];
        for(int i=0;i<n;i++)
            v[i]=x[i];
    }
    vector()
    {
        n=0;
    }

    int &operator[](int n)
    {
        return v[n];
    }

    void operator =(vector &ob)///am nevoie si de aceasta metoda de copiere pentru a copia element cu element
    {
        int i;
        delete []v;
        n=ob.n;
        v=new int[n];
        for(i=0;i<ob.n;i++)
            v[i]=ob.v[i];
    }

    vector(const vector &vec)///constructor de copiere
    {
        delete []v;
        n=vec.n;
        v=new int[vec.n];
        for(int i=0; i<n; i++)
            v[i]=vec.v[i];
    }




    friend istream & operator>>(istream &in , vector & vec);
    friend ostream & operator<<(ostream &out,vector &vec);


};


istream & operator>>(istream &in , vector & vec)
{
    delete []vec.v;
    in>>vec.n;
    vec.v=new int[vec.n];
    cout<<"Scrieti cele "<<vec.n<<" valori: ";
    for(int i=0;i<vec.n;i++)
        in>>vec.v[i];
    return in;
}


ostream & operator<<(ostream &out,vector &vec)
{
    for (int i=0;i<vec.n;i++)
        out<<vec.v[i]<<' ';
    return out;
}


class vectori_de_vectori
{
    int n;
    vector *vdv;


public:

    friend istream & operator>>(istream &in , vectori_de_vectori & vec);
    friend ostream & operator<<(ostream &out,vectori_de_vectori &vec);


    int get_n(){return n;}
    int max()
    {
        int i,s=0;
        for(i=0;i<n;i++)
            if(vdv[i].n>s)
                s=vdv[i].n;
        return s;
    }
    vectori_de_vectori(){n=1;}
    vectori_de_vectori(int val)///constructor de initializare cu o valoare
    {
        int i,j,nr_elem;
        delete []this->vdv;
        cout<<"Scrieti numarul de vectori :";
        cin>>n;
        this->n=n;
        this->vdv=new vector[n];
        for(i=0;i<n;i++)
            {
                cout<<"Numarul de componente din vectorul "<<i+1<<" :";
                cin>>nr_elem;
                delete []this->vdv[i].v;
                vdv[i].v=new int[nr_elem];
                this->vdv[i].n=nr_elem;
                for(j=0;j<nr_elem;j++)
                    vdv[i][j]=val;
            }
    }

    void operator =(vectori_de_vectori const &ob)
    {
        int i;
        for(i=0;i<ob.n;i++)
            delete []ob.vdv[i].v;
        n=ob.n;
        for(i=0;i<ob.n;i++)
            {
                vdv[i].v=new int[ob.vdv[i].n];
                vdv[i]=ob.vdv[i];
            }
    }
    vectori_de_vectori(const vectori_de_vectori &ob)
    {
        int i;
        for(i=0;i<n;i++)
           delete []vdv[i].v;
        delete [] vdv;
        n=ob.n;
        vdv=new vector[n];
        for(i=0;i<n;i++)
            vdv[i]=ob.vdv[i];
    }///constructor de copiere

    ~vectori_de_vectori()
    {
        for(int i=0;i<n;i++)
           delete []vdv[i].v;
        n=0;
        delete [] vdv;
    }///destructor(daca e cazul-alocare statica se seteaza vectorul cu 0, alocare dinamica= dezalocare zona de memorie)


    int** tomatrix(int &n,int &m)
    {
        int i,s=this->max(),j;
        int** a;
        a=new int*[this->n];
        for(i=0;i<this->n;i++)
            {
                a[i]=new int[s];
                for(j=0;j<s;j++)
                        a[i][j]=0;
            }
        for(i=0;i<this->n;i++)
            {
                for(j=0;j<this->vdv[i].n;j++)
                    a[i][j]=this->vdv[i].v[j];
            }
        n=this->n;
        m=s;
        return a;
    }///metoda publica prin care se creeaza o matrice de numere intregi cu nr linii=dim si nr coloane=max dim vectorilor declarati, elementele sunt valorile vectorilor,adaugandu-se 0-uri

    int** operator +(vectori_de_vectori &ob)
    {
        int i,j,x,y,s,t,cmax,lmax;
        int **a=this->tomatrix(x,y),**b = ob.tomatrix(s,t), **rez;
        if(x<s)
                lmax=s;
        else
                lmax=x;
        if(y<t)
                cmax=t;
        else
                cmax=y;
        i=j=0;
        rez=new int*[lmax];
        for(i=0;i<lmax;i++)
        {
            rez[i]=new int[cmax];
            for(j=0;j<cmax;j++)
                rez[i][j]=0;
        }
        i=j=0;
        for(i=0;i<x;i++)
            for(j=0;j<y;j++)
                rez[i][j]+=a[i][j];
        for(i=0;i<s;i++)
            for(j=0;j<t;j++)
                rez[i][j]+=b[i][j];
        return rez;
    }///suma a 2 obiecte de tip vector realizate prin suprrainarcarea operatorului +


};

istream & operator>>(istream &in, vectori_de_vectori & vec)///supraincaracre operator >>
{
    int i;
    cout<<"Scrieti numarul de vectori :";
    in>>vec.n;
    vec.vdv=new vector[vec.n];
    for(i=0;i<vec.n;i++)
    {
        cout<<"Numarul de componente din vectorul "<<i+1<<" :";
        in>>vec.vdv[i];
    }
    return in;
}


ostream & operator<<(ostream &out, vectori_de_vectori &vec)///supraincaracare operator <<
{
   int i;
   out<<"Vectorul de vectori este:\n";
   for(i=0;i<vec.n;i++)
        out<<vec.vdv[i]<<endl;
    return out;
}


int main()
{
    int i,j,**a,n,m,lmax,cmax;
    cout<<"Alocarea cu o singura valoare si afisare:\nScrieti valoarea: ";
    cin>>i;
    vectori_de_vectori v(i);
    cout<<v;
    cout<<"Citirea de la tastatura a unui vector de vector si afisarea acestuia\n";
    vectori_de_vectori w;
    cin>>w;
    cout<<w;
    cout<<"Transformarea unui vector de vectori intr-o matrice se afisarea ei\n";
    a=w.tomatrix(n,m);
    for(i=0;i<n;i++)///afisarea matricei rezultate
    {
        for(j=0;j<m;j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }
    cout<<"Suma a doi vectori de vectori\n";
    a=v+w;
      if(v.get_n()<w.get_n())
                lmax=w.get_n();
        else
                lmax=v.get_n();
        if(v.max()<w.max())
                cmax=w.max();
        else
                cmax=v.max();
    cout<<"Matricea rezultata este: \n";
        for(i=0;i<lmax;i++)///afisarea matricei rezultate
            {
                for(j=0;j<cmax;j++)
                    cout<<a[i][j]<<' ';
                cout<<endl;
            }
    return 0;
}