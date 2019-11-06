#include<bits/stdc++.h>
using namespace std;
int MAX=4;
class Bucket
{
	public:
		int ld=0;
		vector<int>keys;
		bool search(int x)
		{
			for(int i=0;i<keys.size();i++)
				if(keys[i]==x)
					return true;
			return false;
		}
		void display()
		{
			cout<<" { ";
			for(int i=0;i<keys.size();i++)
				cout<<keys[i]<<" ";
			cout<<" } ";
		}
		void insert(int x)
		{
			keys.push_back(x);
			cout<<x<<" inserted successfully\n";
		}
		void remove(int x)
		{
			auto it=find(keys.begin(),keys.end(),x);
			keys.erase(it);
			cout<<x<<" remove\n";
		}
};
class Hashmap
{
	public:
		map<int,Bucket *>bmap;
		int gd=0;
		void display()
		{
			for(int i=0;i<(1<<gd);i++)
			{
				cout<<i<<" : ";
				bmap[i]->display();
				cout<<"\n";
			}
		}
		void search(int x)
		{
			int h=x%(1<<gd);
			if(bmap[h]->search(x))
				cout<<x<<" Found\n";
			else
				cout<<x<<" Not Found\n";
		}
		void insert(int x)
		{
			int h=x%(1<<gd);
			if(bmap[h]->keys.size()<MAX)
				bmap[h]->insert(x);
			else
			{
				split(h);
				insert(x);
			}
		}
		void split(int h)
		{
			Bucket * oldB=bmap[h];
			Bucket * newB=new Bucket;
			vector<int> temp;
			for(int i=0;i<oldB->keys.size();i++)
				temp.push_back(oldB->keys[i]);
			oldB->keys.clear();
			if(oldB->ld==gd)
			{
				if(gd!=0)
					for(int i=0;i<(1<<gd);i++)
						bmap[i^(1<<gd)]=bmap[i];

				bmap[h^(1<<gd)]=newB;
				gd++;
				oldB->ld++;
				newB->ld=oldB->ld;
				for(int i=0;i<temp.size();i++)
				{
					int a=temp[i]%(1<<gd);
					bmap[a]->keys.push_back(temp[i]);
				}
			}
			else
			{
				vector<int>hashkeys;
				for(int i=0;i<(1<<gd);i++)
				{
					if(bmap[i]==oldB)
						hashkeys.push_back(i);
				}
				oldB->ld++;
				newB->ld=oldB->ld;
				for(int i=hashkeys.size()/2;i<hashkeys.size();i++)
					bmap[hashkeys[i]]=newB;
				for(int i=0;i<temp.size();i++)
				{
					int a=temp[i]%(1<<gd);
					bmap[a]->keys.push_back(temp[i]);					
				}
			}
		}
		void merge()
		{
			for(int i=0;i<1<<(gd-1);i++)
			{
				Bucket *bucket1=bmap[i];
				Bucket *bucket2=bmap[i^(1<<(bucket1->ld-1))];
				cout<<"Matched : ";
				bucket1->display();
				bucket2->display();
				cout<<"\n";
				if(bucket1!=bucket2 && bucket1->keys.size()+bucket2->keys.size()<=MAX)
				{
					for(int j=0;j<bucket2->keys.size();j++)
						bucket1->keys.push_back(bucket2->keys[j]);
					for(auto j:bmap)
						if(j.second==bucket2)
							bmap[j.first]=bucket1;
							// bmap[i^(1<<(bucket->ld-1))]=bucket1;
					bucket1->ld--;
					delete(bucket2);					
				}
			}
		}
		void shrink()
		{
			for(int i=0;i<(1<<gd);i++)
				if(bmap[i]->ld==gd)
					return;
			cout<<"Shrinked hash map\n";
			gd--;
		}
		void del(int n)
		{
			if(bmap[n%(1<<gd)]->search(n))
			{
				bmap[n%(1<<gd)]->remove(n);
				merge();
				shrink();
				cout<<"Deleted "<<n<<" successfully\n";
			}
			else
				cout<<n<<" not found\n";
		}
};
int main()
{
	Hashmap hp;
	hp.bmap[0]=new Bucket;
	hp.insert(1);
	hp.display();
	cout<<"\n\n";
	hp.insert(2);
	hp.display();
	cout<<"\n\n";
	hp.insert(3);
	hp.display();
	cout<<"\n\n";
	hp.insert(4);
	hp.display();
	cout<<"\n\n";
	hp.insert(5);
	hp.display();
	cout<<"\n\n";
	hp.insert(6);
	hp.display();
	cout<<"\n\n";
	hp.insert(7);
	hp.display();
	cout<<"\n\n";
	hp.insert(8);
	hp.display();
	cout<<"\n\n";
	hp.insert(9);
	hp.display();
	cout<<"\n\n";
	hp.insert(10);
	hp.display();
	cout<<"\n\n";
	hp.insert(11);
	hp.display();
	cout<<"\n\n";
	hp.insert(12);
	hp.display();
	cout<<"\n\n";
	hp.insert(13);
	hp.display();
	cout<<"\n\n";
	hp.insert(14);
	hp.display();
	cout<<"\n\n";
	hp.insert(15);
	hp.display();
	cout<<"\n\n";
	hp.insert(16);
	hp.display();
	cout<<"\n\n";
	hp.insert(17);
	hp.display();
	cout<<"\n\n";
	hp.insert(18);
	hp.display();
	cout<<"\n\n";
	hp.del(18);
	hp.display();
	cout<<"\n\n";
	
	return 0;
}