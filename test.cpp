#include<set>
#include<map> 
#include<io.h>
#include<queue>  
#include<vector>
#include<string>  
#include<iomanip>    
#include<fstream>
#include<sstream>
#include<iostream>  
using namespace std;
const int K=100;
set<string> words;
vector<string> files;
map<int,string> dict;
int maxlength;
int nums=0,tot=0;
string str;
struct Document
{
	int dis;
	int number;
	bool operator<(const Document&a) const  
    {  
        return a.dis<dis;  
    }  
}document[10000];
struct Mydict
{
	int weight;
	string strs; 	
	bool operator<(const Mydict&src) const
	{
    	return src.strs<strs;
	}
}mydict[100000];
set<Mydict> user[100000];
ofstream fout("result.txt");
set<string>::iterator its;
set<Mydict>::iterator set_it;
map<string,int>::iterator it1,it2;
priority_queue< Document,vector<Document>,less<Document> > knn_queue;
vector<int> results[38];
int countresults[38];
//С���� 
int fnumbers[38]=
{
56,6,7,6,2,3,
5,1,1,3,5,6,5,
3,1,3,2,4,2,3,
6,4,4,5,2,3,3,
3,3,6,3,4,2,9,
2,13,10,7,
/*
2227,240,263,235,83,105,
199,44,58,129,214,229,187,
122,42,114,65,166,94,118,
221,143,141,190,93,112,104,
104,111,250,111,150,95,375,
98,515,404,275,
*/
};
char *dictnames[38]=
{
	"D:\\����.txt","D:\\����.txt","D:\\����.txt","D:\\����.txt","D:\\����.txt","D:\\����.txt","D:\\������.txt",
	"D:\\�����.txt","D:\\ˮ��.txt","D:\\����.txt","D:\\�߶���.txt","D:\\ƹ��.txt","D:\\��ë��.txt","D:\\̨��.txt",
	"D:\\����.txt","D:\\����.txt","D:\\��Ӿ.txt","D:\\��ˮ.txt","D:\\����.txt","D:\\���г�.txt","D:\\���.txt",
	"D:\\�ﾶ.txt","D:\\����.txt","D:\\ȭ��.txt","D:\\ˤ��.txt","D:\\�����ȭ��.txt","D:\\����.txt","D:\\����.txt",
	"D:\\����.txt","D:\\������.txt","D:\\��ͧ��Ƥ��ͧ.txt","D:\\��������.txt","D:\\����������ִ�����.txt",
	"D:\\��ѩ��Ŀ.txt","D:\\��ɽ.txt","D:\\����.txt","D:\\����.txt","D:\\ȫ��.txt",
};
char *filepaths1[38]=
{
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\01����",	
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\02����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\03����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\04����",	
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\05����",	
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\06����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\07������",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\08�����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\09ˮ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\10����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\11�߶���",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\12ƹ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\13��ë��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\14̨��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\15����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\16����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\17��Ӿ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\18��ˮ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\19����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\20���г�",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\21���",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\22�ﾶ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\23����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\24ȭ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\25ˤ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\26�����ȭ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\27����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\28����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\29����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\30������",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\31��ͧ��Ƥ��ͧ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\32��������",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\33����������ִ�����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\34��ѩ��Ŀ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\35��ɽ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\36����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\37����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\��������ѵ���ĵ�\\38ȫ��",
};
char *filepaths2[38]=
{
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\01����",	
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\02����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\03����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\04����",	
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\05����",	
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\06����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\07������",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\08�����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\09ˮ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\10����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\11�߶���",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\12ƹ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\13��ë��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\14̨��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\15����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\16����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\17��Ӿ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\18��ˮ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\19����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\20���г�",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\21���",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\22�ﾶ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\23����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\24ȭ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\25ˤ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\26�����ȭ��",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\27����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\28����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\29����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\30������",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\31��ͧ��Ƥ��ͧ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\32��������",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\33����������ִ�����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\34��ѩ��Ŀ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\35��ɽ",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\36����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\37����",
	"C:\\Users\\Administrator\\Desktop\\ʵ��4\\��������\\������������ĵ�\\38ȫ��",
};
	
void getfiles(string path,string exd,vector<string>& files)
{
	long hFile=0;
	struct _finddata_t fileinfo;
	string pathName, exdName;
	if(0!=strcmp(exd.c_str(),""))
	{
		exdName="\\*."+exd;
	}
	else
	{
		exdName="\\*";
	}
	if((hFile=_findfirst(pathName.assign(path).append(exdName).c_str(),&fileinfo))!=-1)
	{
		do
		{
			if((fileinfo.attrib& _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
					getfiles( pathName.assign(path).append("\\").append(fileinfo.name),exd,files);
			}
			else
			{
				if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		}while(_findnext(hFile, &fileinfo)==0);
		_findclose(hFile);
	}
}

void read_text(char *filename)
{
	ifstream ifile(filename);
	ostringstream buf;
	buf.clear();
	str.clear();
	char ch;
	while(buf&&ifile.get(ch)) buf.put(ch);
    str=buf.str();
	unsigned char c1,c2;
	int i=0;
	while(i<str.length())
	{
		if(i+1<str.length())
		{
			c1=(unsigned char)str[i];
			c2=(unsigned char)str[i+1];
			if(c1>=0xb0&&c1<=0xf7&&c2>=0xa1&&c2<=0xfe) i+=2;
			else str.erase(i,1);
		}
		else str.erase(i,1);
	}
	ifile.close();
}

void read_feature(char *pname)
{
	int j;
	ifstream infile(pname,ios::in);
	string sstr,ssstr;
	nums=0;
	int temp;
	int weight;
	while(getline(infile,sstr))
	{
		temp=0;
		weight=0;
		int i=0;
		while(sstr[i]!=' ') i++;
		ssstr=sstr.substr(0,i);
		while(sstr[i]==' ') i++;
		while(i<sstr.length())
		{	
			weight=weight*10+sstr[i]-'0';
			i++;
		}
		mydict[nums].strs=ssstr;
		mydict[nums].weight=1;
		nums++;
		int sleng=ssstr.length();
		if(sleng>maxlength) maxlength=ssstr.length();
		for(j=ssstr.length()-1;j>=0;j--)
		{
			temp+=ssstr[j];
			temp=temp*100;

		}
		dict[temp]=ssstr;
		ssstr.clear();
	}
	infile.close();
}

void pre_knn(char *dictname,char *filepath)
{
	nums=0;
	int i,j,temp;
	dict.clear();
	files.clear();
	read_feature(dictname);
	getfiles(filepath,"txt",files);
 	int size=files.size();
	for(int k=0;k<size;k++)
	{
		string strtemp=files[k];
		int len=strtemp.size();
		string c="\\";
		for(int m=0;m<len;m++)
		{
			if(strtemp[m]=='\\') 
			{
				strtemp.insert(m,c);
				m+=2;
				len=strtemp.size();
			}
		}
		char *f1name=(char *)strtemp.c_str();
		cout<<f1name<<endl;
		read_text(f1name);
		int pos=-1;
		i=j=str.length()-1;
		map<int,string>::iterator map_it; 
		while(i>=0)
		{
			int temp=0;
			int j=i;
			for(;j>=0;j--)
			{
				temp+=str[j];
				temp=temp*100;
				map_it=dict.find(temp);
				if(map_it!=dict.end()&&j!=0)
				{
					if(j%2==0) pos=j;
				}
				if(map_it!=dict.end()&&j==0)
				{
					for(int ii=0;ii<nums;ii++)
					{
						if(str.substr(0,i-j+1)==mydict[ii].strs)
						{
							user[tot].insert(mydict[ii]);
							break;
						}
					}
					i=-1;
					break;
				}
				if(map_it==dict.end()&&(i-j>=maxlength-1||j==0))
				{
					if(pos==-1)
					{
						i-=2;
						break;

					}
					else
					{
						for(int ii=0;ii<nums;ii++)
						{
							if(str.substr(pos,i-pos+1)==mydict[ii].strs)
							{
								user[tot].insert(mydict[ii]);
								break;
							}
						}
						i=pos-1;
						pos=-1;
						break;
					}
				}
			}
		}
		tot++;
	} 	
}

void read_dict(char *pname)
{
	int j;
	dict.clear(); 
	ifstream infile(pname, ios::in);
	string sstr;
	int temp;
	while(getline(infile,sstr))
	{
		temp=0;
		int sleng=sstr.length();
		if(sleng>maxlength) maxlength=sstr.length();
		for(j=sstr.length()-1;j>=0;j--)
		{
			temp+=sstr[j];
			temp=temp*100;

		}
		dict[temp]=sstr;
		sstr.clear();
	}
	infile.close();
}

void count_dis(int i)
{
	int temp=0;
	for(its=words.begin();its!=words.end();its++)
	{
		for(set_it=user[i].begin();set_it!=user[i].end();set_it++)
		{
			if((*its)==(*set_it).strs)
			{
				temp+=(*set_it).weight;
			}
		}
	}
	document[i].dis=temp;
	document[i].number=i;
	if(knn_queue.size()<K) knn_queue.push(document[i]);
	else if(document[i].dis>knn_queue.top().dis) 
	{
		knn_queue.pop();
		knn_queue.push(document[i]);
	}
}

void solve(int tempnum)
{
	int adjust=1;
	int interval=1;
	int categorys[38];
	for(int i=0;i<38;i++) categorys[i]=0;
	while(!knn_queue.empty())
	{
		int t=knn_queue.top().number;
		knn_queue.pop();
		if(t<2227) categorys[0]+=adjust;
		//���� 
		if(t>=2227&&t<2467) categorys[1]+=adjust;
		//���� 
		if(t>=2467&&t<2730) categorys[2]+=adjust;
		//���� 
		if(t>=2730&&t<2965) categorys[3]+=adjust;
		//���� 
	//	if(t>=2965&&t<3048) categorys[4]+=adjust;
	//	if(t>=3048&&t<3153) categorys[5]+=adjust;
	//	if(t>=3153&&t<3352) categorys[6]+=adjust;
	//	if(t>=3352&&t<3396) categorys[7]+=adjust;
	//	if(t>=3396&&t<3454) categorys[8]+=adjust;
		if(t>=2965&&t<3094) categorys[9]+=adjust;
		//���� 
		if(t>=3094&&t<3308) categorys[10]+=adjust;
		//�߶��� 
		if(t>=3308&&t<3537) categorys[11]+=adjust;
		//ƹ�� 
		if(t>=3537&&t<3724) categorys[12]+=adjust;
		//��ë�� 
		if(t>=3724&&t<3846) categorys[13]+=adjust;
		//̨�� 
	//	if(t>=3846&&t<4377) categorys[14]+=adjust;
		if(t>=3846&&t<3960) categorys[15]+=adjust;
		if(t>=3960&&t<4025) categorys[16]+=adjust;
		if(t>=4025&&t<4191) categorys[17]+=adjust;
		if(t>=4191&&t<4285) categorys[18]+=adjust;
		if(t>=4285&&t<4403) categorys[19]+=adjust;
		if(t>=4403&&t<4624) categorys[20]+=adjust;
		if(t>=4624&&t<4767) categorys[21]+=adjust;
		if(t>=4767&&t<4908) categorys[22]+=adjust;
		if(t>=4908&&t<5098) categorys[23]+=adjust;
	//	if(t>=5629&&t<5722) categorys[24]+=adjust;
	//	if(t>=5722&&t<5834) categorys[25]+=adjust;
	//	if(t>=5834&&t<5938) categorys[26]+=adjust;
		if(t>=5098&&t<5202) categorys[27]+=adjust;
	//	if(t>=6042&&t<6153) categorys[28]+=adjust;
		if(t>=5202&&t<5452) categorys[29]+=adjust;
	//	if(t>=6403&&t<6514) categorys[30]+=adjust;
	//	if(t>=6514&&t<6664) categorys[31]+=adjust;
		if(t>=5452&&t<5547) categorys[32]+=adjust;
		if(t>=5547&&t<5922) categorys[33]+=adjust;
	//	if(t>=7134&&t<7232) categorys[34]+=adjust;
	//	if(t>=7232&&t<7747) categorys[35]+=adjust;
	//	if(t>=7747&&t<8151) categorys[36]+=adjust;
	//	if(t>=8151) categorys[37]+=adjust;
		adjust+=interval;
		interval++;	
	} 
	/*
	categorys[37]=0;
	categorys[36]=0;
	categorys[35]=0;
	categorys[34]=0;
	categorys[31]=0;
	categorys[30]=0;
	categorys[28]=0;
	categorys[26]=0;
	categorys[25]=0;
	categorys[24]=0;
	categorys[14]=0;
	categorys[8]=0;
	categorys[7]=0;
	categorys[6]=0;
	categorys[5]=0;
	categorys[4]=0;
	*/
	for(int i=0;i<38;i++)
	{
		categorys[i]=categorys[i]*10000/fnumbers[i];
	}
	int maxelement=0,maxpos;
	for(int i=0;i<38;i++)
	{
		if(categorys[i]>maxelement) 
		{
			maxelement=categorys[i];
			maxpos=i;
		}
	}
	results[tempnum].push_back(maxpos);
	countresults[maxpos]++;
}

void train(char *filepath,int tempnum)
{
	int i,j;
	files.clear();
	getfiles(filepath,"txt",files);
 	int size=files.size();
	for(int k=0;k<size;k++)
	{
		string strtemp=files[k];
		int len=strtemp.size();
		string c="\\";
		for(int m=0;m<len;m++)
		{
			if(strtemp[m]=='\\') 
			{
				strtemp.insert(m,c);
				m+=2;
				len=strtemp.size();
			}
		}
		char *f1name=(char *)strtemp.c_str();
		fout<<f1name<<endl;
		cout<<"���ڴ���"<<f1name<<endl; 
		read_text(f1name);
		int pos=-1;
		i=j=str.length()-1;
		map<int,string>::iterator map_it;
		words.clear(); 
		while(!knn_queue.empty()) knn_queue.pop();
		while(i>=0)
		{
			int temp=0;
			int j=i;
			for(;j>=0;j--)
			{
				temp+=str[j];
				temp=temp*100;
				map_it=dict.find(temp);
				if(map_it!=dict.end()&&j!=0)
				{
					if(j%2==0) pos=j;
				}
				if(map_it!=dict.end()&&j==0)
				{
					words.insert(str.substr(0,i-j+1));
					i=-1;
					break;
				}
				if(map_it==dict.end()&&(i-j>=maxlength-1||j==0))
				{
					if(pos==-1)
					{
						i-=2;
						break;
					}
					else
					{
						words.insert(str.substr(pos,i-pos+1));
						i=pos-1;
						pos=-1;
						break;
					}
				}
			}
		}
		for(int ii=0;ii<tot;ii++) count_dis(ii);
		solve(tempnum);
	} 	
}

int main()
{
	char *filepath,*dictname;
	for(int i=0;i<38;i++)
	{
		if(i!=37&&i!=36&&i!=35&&i!=34&&i!=31&&i!=30&&i!=28&&i!=26&&i!=25&&i!=24&&i!=14&&i!=8&&i!=7&&i!=6&&i!=5&&i!=4)
		{
			dictname=dictnames[i];
			filepath=filepaths1[i];
			pre_knn(dictname,filepath);
		}
	}
	read_dict("�ʵ�.txt");
	for(int i=0;i<38;i++)
	{
		if(i!=37&&i!=36&&i!=35&&i!=34&&i!=31&&i!=30&&i!=28&&i!=26&&i!=25&&i!=24&&i!=14&&i!=8&&i!=7&&i!=6&&i!=5&&i!=4)
		{
			filepath=filepaths2[i];
			train(filepath,i);
		}
	}
	for(int i=0;i<38;i++)
	{
		if(i!=37&&i!=36&&i!=35&&i!=34&&i!=31&&i!=30&&i!=28&&i!=26&&i!=25&&i!=24&&i!=14&&i!=8&&i!=7&&i!=6&&i!=5&&i!=4)
		{
			cout<<i<<endl;
			fout<<i<<endl;
			int temps=0;
			for(int j=0;j<results[i].size();j++)
			{
				if(results[i][j]==i) temps++;
			}
			double tt=temps/countresults[i];
			cout<<temps<<" "<<countresults[i]<<" "<<tt<<endl;
			fout<<temps<<" "<<countresults[i]<<" "<<tt<<endl;
		}
	}
	fout.close();
	return 0;
}
