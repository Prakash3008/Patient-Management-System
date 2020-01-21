#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;
class patient
{
private:
    long long int pid;
    char pname[25];
    char pdisease[25];
    long long int pphno;
    char pcondoc[25];
    char ptype[15];
    int daysstayed;
    int visited;
    char date[25];
    patient* next;
public:
    patient()
    {
        pid=0;
        next=NULL;
        daysstayed=0;
        visited=0;
    }
    void setpatient();
    void getpatient();
    void setfile();
    void getfile();
    void disppatient(patient hash[]);
    void insert(patient hash[],patient pt);
    void nextpat(patient pt);
    void storeinfile();
    void storeoutfile();
    void disin(int x);
    void disout(int x);
    void storeout();
    void finddis(char dis[]);
    void storehash(patient hash[]);
    //void freefile(patient hash[]);
};
void patient::disppatient(patient hash[])
{
	for(int i=0;i<10;i++)
	{
		                                                       cout<<"Index :: "<<i<<"\n"<<endl;
		hash[i].getpatient();
		cout<<"\n";
    }
}
int length(string a)
{
    //int len=strlen(a);
    return a.size();
}
bool validate(char *ch)
{
    for(int i=0;ch[i]!='\0';i++)
    {
        if(isalnum(ch[i]) && isdigit(ch[i]))
            return true;
    }
}
bool numer(string n)
{
    for(int i=0;i<n.size();i++)
    {
        if(n[i]>='a' && n[i]<='z' || n[i]>='A' && n[i]<='Z')
            return true;
    }
}

void patient::setpatient()
{
    char type,t,pn[20],pd[20],pdoc[20];
    string id,phno,sta,vis;
    try
    {
            cout<<"______________________________________________________________________________________________________________________________________________________________________\n";
            cout<<"\nPatient Type (i-Inpatient or o-Outpatient) : ";
            cin>>t;
        if(t=='o' | t=='i')
            type=t;
        else
           throw "\nPlease enter the valid type of patient either inpatient or outpatient \n";
            cout<<"______________________________________________________________________________________________________________________________________________________________________\n";
            cout<<"\nPatient ID : ";
            cin>>id;
    if(length(id)!=9)
        throw "\nEnter a valid Patient ID\n";
            cout<<"________________________________________________________________________________________________________________________________________________________________________\n";
            cout<<"\nPatient Name : ";
            cin>>pn;
    if(validate(pn))
        throw "\nEnter the correct name\n";
            cout<<"_________________________________________________________________________________________________________________________________________________________________________\n";
            cout<<"\nPatient Phone Number : ";
            cin>>phno;
    if(length(phno)!=10)
        throw "\nEnter a valid Phone Number\n";
            cout<<"__________________________________________________________________________________________________________________________________________________________________________\n";
            cout<<"\nDisease of the Patient : ";
            cin>>pd;
    if(validate(pd))
        throw "\nGive a Proper Name\n";
            cout<<"___________________________________________________________________________________________________________________________________________________________________________\n";
            cout<<"\nDoctor Consulted : ";
            cin>>pdoc;
    if(validate(pdoc))
        throw "\nEnter the correct doctor name\n";
       else
    {
        this->pid=stoll(id);
        strcpy(this->pname,pn);
        this->pphno=stoll(phno);
        strcpy(this->pdisease,pd);
        strcpy(this->pcondoc,pdoc);
    }
    if(type=='i')
    {
        strcpy(ptype,"Inpatient");
        cout<<"\n\t\t# No.of days stayed : ";
        cin>>sta;
        if(numer(sta))
            throw "\nGive an appropriate input\n";
        else
            this->daysstayed=stoi(sta);
        visited=0;
    }
    else if(type=='o')
    {
        strcpy(ptype,"Outpatient");
        cout<<"\n\t\t #No.of times consulted the doctor : ";
        cin>>vis;
        if(numer(vis))
            throw "\nGive an appropriate input\n";
        else
            this->visited=stoi(vis);
        daysstayed=0;
    }
    }
    catch(const char *mg)
    {
        cout<<"=============================================================\n";
        cout<<"\t\t"<<mg<<endl<<"\n";
        cout<<"=============================================================\n";
        return;
    }
}
void patient::setfile()
{
	fstream infile;
	infile.open("patient.dat",ios::app|ios::in|ios::binary);
	infile.write((char *)&*this,sizeof(class patient));
	infile.close();
}
void patient::getpatient()
{
    if(pid!=0)
    {
    cout<<"_________________________________________________________________________________________________________________________________________________________________________\n";
    cout<<"\nPatient Type : "<<ptype<<endl;
    cout<<"|_______________________________________________________________________________________________________________________________________________________________________|\n";
    cout<<"\nPatient ID : "<<pid<<endl;
    cout<<"|_______________________________________________________________________________________________________________________________________________________________________|\n";
    cout<<"\nPatient Name : "<<pname<<endl;
    cout<<"|_______________________________________________________________________________________________________________________________________________________________________|\n";
    cout<<"\nPatient Phone Number : "<<pphno<<endl;
    cout<<"|_______________________________________________________________________________________________________________________________________________________________________|\n";
    cout<<"\nDisease of the Patient : "<<pdisease<<endl;
    cout<<"|_______________________________________________________________________________________________________________________________________________________________________|\n";
    cout<<"\nDoctor Consulted : "<<pcondoc<<endl;
    cout<<"|_______________________________________________________________________________________________________________________________________________________________________|\n";
    if(daysstayed!=0)
        cout<<"\n\t\t\t#  No.of days stayed : "<<daysstayed<<endl;
    if(visited!=0)
         cout<<"\n\t\t\t#  No.of times consulted the doctor : "<<visited<<endl;
    }
    if(next!=NULL)

	{
		next->getpatient();
		return;
	}
	else
	return;
	cout<<"\n\n"<<endl;
}

int findindex(int key)
{
    int v = key % 1000;
    key /= 1000;
    while(v < key)
        v=v*1000000;
    key=v+key;
    return key % 10;
}
void patient::insert(patient hash[],patient pt)
{
    int hashindex=findindex(pid);
    if(hash[hashindex].pid==0)
    {
        hash[hashindex]=pt;
        return;
    }
    else
    {
        hash[hashindex].nextpat(pt);
    }
}
void patient::nextpat(patient pt)
{
	if(this->next==NULL)
	{
		this->next=new patient;
		*this->next=pt;
		return;
	}
	else
	{
		this->next->nextpat(pt);
		return;
	}
}

void patient::getfile()
{
			fstream outfile;
			outfile.open("patient.dat",ios::in|ios::binary);
			while(outfile.read((char *)&*this,sizeof(class patient)))
			{

				this->getpatient();
			}
			outfile.close();
}
//######INPATIENT DOCTOR#########
int day[100];
int count;
void patient::storeinfile()
{
			fstream outfile;
			outfile.open("patient.dat",ios::in|ios::binary);
			while(outfile.read((char *)&*this,sizeof(class patient)))
			{
                if(this->daysstayed!=0)
                {
                    day[count]=this->daysstayed;
                    count++;
                }

			}
			outfile.close();
}
void patient::disin(int x)
{
            fstream outfile;
			outfile.open("patient.dat",ios::in|ios::binary);
			while(outfile.read((char *)&*this,sizeof(class patient)))
			{
				if(this->daysstayed==x)
                {
                    cout<<"__________________________________________________________________________________________________________________________________________________________\n";
                    cout<<"\nBest Inpatient Doctor : "<<pcondoc;
                    cout<<"|_________________________________________________________________________________________________________________________________________________________|\n";
                    cout<<"\nNo.of days stayed : "<<daysstayed;
                    cout<<"|_________________________________________________________________________________________________________________________________________________________|\n";
                    //cout<<"\nNo.of times consulted the doctor : "<<visited;
                }
			}
			outfile.close();
}
//#########INPATIENT END##############
//#########OUTPATIENT DOCTOR############
int visit[100];
int count1;
void patient::storeoutfile()
{
			fstream outfile;
			outfile.open("patient.dat",ios::in|ios::binary);
			while(outfile.read((char *)&*this,sizeof(class patient)))
			{
                if(this->visited!=0)
                {
                    visit[count1]=this->visited;
                    count1++;
                }

			}
			outfile.close();

}
void patient::disout(int x)
{
            fstream outfile;
			outfile.open("patient.dat",ios::in|ios::binary);
			while(outfile.read((char *)&*this,sizeof(class patient)))
			{
				if(this->visited==x)
                {
                	cout<<"___________________________________________________________________________________________________________________________________________\n";
                    cout<<"Best Outpatient Doctor : "<<pcondoc;
                    cout<<"|__________________________________________________________________________________________________________________________________________|\n";
                    cout<<"No.of times consulted the doctor : "<<visited;
                    cout<<"|__________________________________________________________________________________________________________________________________________|\n";
                }
			}
			outfile.close();
}
void merge(int x[], int left, int mid, int right)
{
    int i, j, k;
    int a = mid - left + 1;
    int b =  right - mid;
    int Le[a], Ri[b];
    for (i = 0; i < a; i++)
        Le[i] = x[left + i];
    for (j = 0; j < b; j++)
        Ri[j] = x[mid + 1+ j];
    i = 0;
    j = 0;
    k = left;
    while (i < a && j < b)
    {
        if (Le[i] <= Ri[j])
        {
            x[k] = Le[i];
            i++;
        }
        else
        {
            x[k] = Ri[j];
            j++;
        }
        k++;
    }
    while (i < a)
    {
        x[k] = Le[i];
        i++;
        k++;
    }
    while (j < a)
    {
        x[k] = Ri[j];
        j++;
        k++;
    }
}
void mergeSort(int x[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(x, l, m);
        mergeSort(x, m+1, r);
        merge(x, l, m, r);
    }
}
void patient::finddis(char dis[])
{
	fstream outfile;
	outfile.open("patient.dat",ios::in|ios::binary);
	while(outfile.read((char *)&*this,sizeof(class patient)))
	{
		if(strcmp(dis,this->pdisease)==0)
		{
			this->getpatient();
		}
		else
		{
			cout<<"\n\n\t\t\t\t\tSearching! ! !\n";
		}
	}
	outfile.close();
}
/*void patient::freefile(patient hash[])
{
    for(int i=0;i<10;i++)
    {
        hash[i].pid=0;
        hash[i].next=NULL;
        hash[i].daysstayed=0;
        hash[i].visited=0;
    }
}*/
void patient::storehash(patient hash[])
{
    fstream file;
    //freefile(hash);
    file.open("patient.dat",ios::in|ios::binary);
    while(file.read((char *)&*this,sizeof(class patient)))
    {
        insert(hash,*this);
    }
    file.close();
}
int main()
{
    patient pt;
    patient hash[10];
    pt.storehash(hash);
    int ch;
    while(1)
    {

        cout<<"|____________________________________________+++++++++++++++++++++OPTIONS++++++++++++++++++++++++_______________________________________________________|\n";
 		cout<<"|                                            [    1.Admit Patient                               ]                                                       |\n";
		cout<<"|                                            [    2.Display Patient                             ]                                                       |\n";
		cout<<"|                                            [    3.Display Best Doctor                         ]                                                       |\n";
		cout<<"|                                            [    4.Display Patient with a Particular Disease   ]                                                       |\n";
		cout<<"|                                            [    5.Exit                                        ]                                                       |\n";
		cout<<"|                                            ____________________________________________________                                                       |\n";
        cout<<"|_______________________________________________________________________________________________________________________________________________________|\n";
		cout<<"|                                                                                                                                                       |\n";
		cout<<"|    Enter your Choice :                                                                                                                                |\n";
        cout<<"|_______________________________________________________________________________________________________________________________________________________|\n\n\n\n";
        cin>>ch;

    	switch(ch)
        {
            case 1:system("cls");
			       pt.setpatient();
                   pt.setfile();
                   pt.insert(hash,pt);
                   break;
            case 2: system("cls");
			        int c;
			        cout<<" ________________________________________________------TABLE & RECORD------________________________________________________________\n";
			        cout<<"|                                                                                                                                  |\n";
                    cout<<"|                                   # 1.Display Hash Table                                                                         |\n";
 					cout<<"|                                       #2.Display Patient Records                                                                 |\n";
 					cout<<"|__________________________________________________________________________________________________________________________________|\n";
                    cout<<"Enter the Choice :";
					cin>>c;
                    switch(c)
                    {
                        case 1:system("cls");
						        pt.disppatient(hash);
                                break;

                        case 2: system("cls");
						        cout<<endl<<endl;
                                pt.getfile();
                                cout<<endl<<endl;
                                break;
                                default:                    cout<<"\n\t\t|=========================|\n";
								                            cout<<"\t\t|Enter a Valid Option ! ! |\n";
								                            cout<<"\t\t|=========================|\n\n";
                    }
                    break;
            case 3: system("cls");
			        int cc,in,mini;
			        cout<<" ___________________________________________________^^^^^^ PREFERED DOCTOR^^^^^^____________________________________________________________________________\n";
                    cout<<"|                                  # 1.Inpatient Doctor                                                                                                     |\n";
					cout<<"|                                     # 2.Outpatient Doctor\nChoice                                                                                         |\n";
					cout<<"|___________________________________________________________________________________________________________________________________________________________|\n";
                    cin>>cc;
                    switch(cc)
                    {
                        case 1: system("cls");
						        count=0;
                                pt.storeinfile();
                                mergeSort(day,0,count-1);
                                in=day[0];
                                pt.disin(in);
                                break;
                        case 2: system("cls");
						        count1=0;
                                pt.storeoutfile();
                                mergeSort(visit,0,count1-1);
                                mini=visit[0];
                                pt.disout(mini);
                                break;
                                default:                             cout<<"\n\t\t=========================\n";
								                                     cout<<"\t\t| Enter a Valid Option!!|\n";
								                                     cout<<"\t\t=========================\n\n";
                    }
                    break;
            case 4: system("cls");
			        char dis[20];
			        cout<<" __________________________________________________________________________________________________________________________________________________\n";
                    cout<<"|\tDisease Name :                                                                                                                                  |\n";
                    cout<<"|__________________________________________________________________________________________________________________________________________________|\n";
                    cin>>dis;
                    pt.finddis(dis);
                    break;
            case 5:system("cls");
			        exit(0);
            default:                                                cout<<"\n\t\t=======================\n";
			                                                        cout<<"\t\t|Enter a Valid Option!|\n";
			                                                        cout<<"\t\t=======================\n\n";
        }
    }
}

