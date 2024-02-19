#include <iostream>
#include <list>
#include <fstream>
using namespace std;
ifstream f("mergeheap.in");
ofstream g("mergeheap.out");
struct N
{
    int val,NumarCopii;
    N* P;
    N* fiu;
    N* frate;

};

N* NN(int valoare)
{
    N* nou= new N;
    nou->val=valoare;
    nou->P=nou->fiu=nou->frate=nullptr;
    nou->NumarCopii=0;
    return nou;
}

struct HeapBionomial {
    list<N*> arbori;
    ///reunim arborii cu val mai mare va fi parintele(radacina) arborelui cu val mai mica(va fi adăugat ca un subarbore al rădăcinii)

    N* reuniune_arbori(N* m, N* n){
        if (m->val < n->val) {
            N* temp = m;
            m = n;
            n = temp;
        }
        m->NumarCopii++;
        n->P = m;
        n->frate = m->fiu;
        m->fiu = n;
        return m;
    }



    ///pastram ordinea crescatoare a cheilor arborilor binomiali si pe cei cu nr de copii egal ii reunim

    void modificarearbori() {
        arbori.sort([](N *a, N *b) { return a->NumarCopii < b->NumarCopii; });
        ///avem o lista cu toti arborii din cele 2 heap uri in ordine cresc a valorilor
        if (arbori.size() <= 1) {
            return;
        }
        else {

            list<N *>::iterator st;
            list<N *>::iterator cnt;
            list<N *>::iterator dr;

            st = arbori.begin();
            cnt= st;
            cnt++;
            dr= cnt;
            dr++;

            while(cnt!=arbori.end())
            {
                if(dr!=arbori.end())
                {
                    if((*st)->NumarCopii==(*cnt)->NumarCopii && (*cnt)->NumarCopii!=(*dr)->NumarCopii)///am reunc1 arborii cu acelasi nr de copii
                    {
                        *st= reuniune_arbori(*st,*cnt);
                        cnt=arbori.erase(cnt);
                        dr++;
                    }
                    else
                    {
                        st++;
                        cnt++;
                        dr++;
                    }
                }
                else
                {
                    if((*st)->NumarCopii==(*cnt)->NumarCopii)
                    {
                        *st= reuniune_arbori(*st,*cnt);
                        arbori.pop_back();
                    }

                    cnt=arbori.end();
                }
            }
    }
};

    ///reunim heapuri

    void unireHeap(HeapBionomial& heap2)
    {
        list<N*> HeapFinal;
        list<N*> :: iterator m, n;
        m=arbori.begin();
        n= heap2.arbori.begin();

        while(m!=arbori.end() && n!=heap2.arbori.end())
        {
            if((*n)->NumarCopii>=(*m)->NumarCopii)
            {
                HeapFinal.push_front(*m);
                m++;
            }
            else
            {
                HeapFinal.push_front(*n);
                n++;
            }
            while (m!=arbori.end())
            {
                HeapFinal.push_front(*m);
                m++;
            }

            while (n!=heap2.arbori.end())
            {
                HeapFinal.push_front(*n);
                n++;
            }
        }

        heap2.arbori.clear();
        arbori=HeapFinal;
        modificarearbori();

    }

    /// inseram un nod nou in heap(in lista arbori)
    void inserare_val(int valoare)
    {
        N* nou=NN(valoare);
        arbori.push_back(nou);
        modificarearbori();
    }

    ///gasim radacina cu valoarea maxima si o eliminam, apoi adaugam arboriceii ramasi in lista de arbori pe care o arajam corespunzator

    void eliminare()
    {
        if (arbori.empty()) {
            return ;
        }

        auto c1 = arbori.begin();
        N* max = *c1;
        while (c1 != arbori.end()) {
            if ((*c1)->val > max->val) {
                max= *c1;
            }
            c1++;
        }

        arbori.remove(max);
        list<N*> arboricei;
        N* sa=max->fiu;
        g<<(*max).val<<endl;
        while (sa!=NULL)
        {
            arboricei.push_front(sa);
            sa=sa->frate;
        }

        auto c12 = arboricei.begin();
        while (c12!= arboricei.end())
        {
            arbori.push_back(*c12);
            c12++;
        }
        modificarearbori();
    }

};

int main()
{
    int multime,operatii;
    f>>multime>>operatii;
    HeapBionomial Heap[101];
    int numarOperatii, val,c,i,j,t;
    for (t=1;t<=operatii;t++){
        f>>numarOperatii;
        if (numarOperatii==1){
            f>>c;
            f>>val;
            Heap[c].inserare_val(val);

        } else if (numarOperatii==2){
            f>>c;
            Heap[c].eliminare();
        } else if (numarOperatii==3){
            f>>i>>j;
            Heap[i].unireHeap(Heap[j]);
        }
    }
    return 0;
}
