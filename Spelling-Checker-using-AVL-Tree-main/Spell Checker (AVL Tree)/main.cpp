/*
Developed By Atif Ali
			 Bilal Ahmed
			 Muhammad
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <ctype.h>
#include <conio.h>
#include<sstream>
#include<windows.h>

using namespace std;

class CorrectedWords
{
	public:
		string mistake, correction;
		
		CorrectedWords():mistake(""),correction("")
		{
		}		
		
		friend ostream& operator<<(ostream&, CorrectedWords);
};

ostream& operator<<(ostream& o, const CorrectedWords ob)
{
	o << ob.mistake << "         -->\t" << ob.correction << endl;
	return o;
}

template<class T>
class LLNode
{
	public:
		T data;
		LLNode *next;
		
		LLNode():data(""),next(NULL)
		{
		}
		
		LLNode(T data):data(data),next(NULL)
		{
		}
};

template<class T>
class LinkedList{
	public:
		LLNode<T> *head;
		
		LinkedList():head(NULL)
		{
		}
		
		void insert(T data)
		{
    		LLNode<T> *newLLNode = new LLNode<T>(data);
			if(head == NULL){
				head = newLLNode;
				return;
			}
		
			else{
				LLNode<T> *temp = head;
				while(temp->next != NULL){
					temp = temp->next;
				}
				temp->next = newLLNode; 
			}
		}
	
		int getLength()
		{
			int counter = 0;
			LLNode<T> *temp = head;
			while(temp != NULL)
			{
				counter++;
				temp = temp->next;
			}
			return counter;
		}	
		
		T searchWord(int num)
		{
			LLNode<T> *temp = head;
			for(int i=0; i < num-1; i++)
			{
				temp = temp->next;
			}
			return temp->data;
		}
		
		string searchMistake(string word)
		{
			LLNode<CorrectedWords> *temp = head;
			while(temp != NULL)
			{
				if(temp->data.mistake == word)
				{
					return temp->data.correction;
				}
				temp = temp->next;
			}
			return "N/A";
		}
	
		void print()
		{
			LLNode<T> *temp = head;
			int i= 1;
			while(temp != NULL)
			{
				cout<<"\n\t\t";
				cout << i<<"."<<temp->data;
				temp = temp->next;
				i++;
			}
		}
};


class Node
{
	public:
		Node *right, *left;
		string data="";
		int height;
		
		Node(string str):data(str),left(NULL),right(NULL),height(1)
		{
		}
};

class BST
{
	public:
		int getHeight(Node *N)
		{
			if (N == NULL)
				return 0;
			return N->height;
		}
		
		int max(int a, int b)
		{
			return (a > b)? a : b;
		}
		
		Node* newNode(string key)
		{
			Node* node = new Node(key);
			return node;
		}
		
		Node *rightRotate(Node *y)
		{
			Node *x = y->left;
			Node *T2 = x->right;
		
			x->right = y;
			y->left = T2;
		
			y->height = max(getHeight(y->left),
							getHeight(y->right)) + 1;
			x->height = max(getHeight(x->left),
							getHeight(x->right)) + 1;
		
			return x;
		}
		
		Node *leftRotate(Node *x)
		{
			Node *y = x->right;
			Node *T2 = y->left;
		
			y->left = x;
			x->right = T2;
		
			x->height = max(getHeight(x->left),
							getHeight(x->right)) + 1;
			y->height = max(getHeight(y->left),
							getHeight(y->right)) + 1;
		
			return y;
		}
		
		int getBalance(Node *N)
		{
			if (N == NULL)
				return 0;
			return getHeight(N->left) - getHeight(N->right);
		}
		
		Node* insert(Node* node, string key)
		{
			if (node == NULL)
				return(newNode(key));
		
			else if (key < node->data)
				node->left = insert(node->left, key);
			else if (key > node->data)
				node->right = insert(node->right, key);
			node->height = 1 + max(getHeight(node->left),
								getHeight(node->right));
		
			int balance = getBalance(node);
		
			if (balance > 1 && key < node->left->data)
				return rightRotate(node);
		
			if (balance < -1 && key > node->right->data)
				return leftRotate(node);
		
			if (balance > 1 && key > node->left->data)
			{
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
			if (balance < -1 && key < node->right->data)
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			return node;
		}
		
		void inorder(Node *root)
		{
			if(root == NULL)
			{
				return;
			}
			else
			{
				inorder(root->left);
				cout << root->data << endl;
				inorder(root->right);
			}
		}
		
		bool searchAvltree(Node* root, string word){
			if(root == NULL)
            	return false;
        
        	else if(word == root->data)
            	return true;
        
        	else if(word < root->data)
            	return searchAvltree(root->left, word);
        
        	else if(word > root->data)
            	return searchAvltree(root->right, word);
            	
            return false;
		}
};

//lower case alphabets.
char lower_alpha[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int partition(string str, int low, int high)
{
	int pivot = str[high]; // pivot
	int i = (low- 1);
	for (int j = low; j <= high - 1; j++) 
	{
		if (str[j] < pivot) 
		{
			i++;
			swap(str[i], str[j]);
		}
	}
	swap(str[i + 1], str[high]);
	return (i + 1);
}

void quickSort(string str, int low, int high)
{
	if (low < high) 
	{
		int pi = partition(str, low, high);

		quickSort(str, low, pi - 1);
		quickSort(str, pi + 1, high);
	}
}

//function to show the correct spelling if arrangement of word is incorrect.
int incorrectArrangement(string input, Node *root)
{
    string line;
    string Xinput = input, Ninput, permutations, Tinput, Tline, Nline, Xline = line;
    int found = 0;
        
        if(root==NULL){
        	return 0;
		}
		else{
			line= root->data;
			int len = Xinput.size(), flen = line.size();
        if (len == flen)
        {
            for (int i=1; i<Xinput.length(); i++)
                Ninput.push_back(input[i]);
            for (int i = 1; i < flen; i++)
                Nline.push_back(Xline[i]);
            Xinput.resize(1);
            Xline.resize(1);
            sort(Nline.begin(),Nline.end());
            sort(Ninput.begin(), Ninput.end());
//            quickSort(Nline, 0, Nline.length());
//            quickSort(Ninput, 0, Ninput.length());
			Tinput = Xinput + Ninput;
            Tline = Xline + Nline;
            if (Tinput == Tline)
            {
                found = 1;
                cout<<"\t\t"<<line<<endl;
            }
        }
		}
    
    return found || (incorrectArrangement(input, root->left)) || (incorrectArrangement(input, root->right));
}

void incorrectArrangement(string input, Node *root, LinkedList<string> &ob)
{
    string line;
    string Xinput = input, Ninput, permutations, Tinput, Tline, Nline, Xline = line;
    int found = 0;
        
        if(root==NULL){
        	return ;
		}
		else{
			line= root->data;
			int len = Xinput.size(), flen = line.size();
        if (len == flen)
        {
            for (int i=1; i<Xinput.length(); i++)
                Ninput.push_back(input[i]);
            for (int i = 1; i < flen; i++)
                Nline.push_back(Xline[i]);
            Xinput.resize(1);
            Xline.resize(1);
            sort(Nline.begin(),Nline.end());
            sort(Ninput.begin(), Ninput.end());
            Tinput = Xinput + Ninput;
            Tline = Xline + Nline;
            if (Tinput == Tline)
            {
                found = 1;
                ob.insert(line);
            }
        }
		}
    
    incorrectArrangement(input, root->left,ob);
    incorrectArrangement(input, root->right,ob);
}

//function to show correct spelling if exchanged character is present in the given word
int exchangedCharacters (string input, Node *root)
{
    string line, Xinput;
    int found = 0;
    if(root==NULL){
    	return 0;
	}
	else{
		line = root -> data;
	int len = input.size(), flen = line.size();
        if (len == flen)
        {
            for (int i = len-1; i >= 0 ; i--)
            {
                Xinput = input;
                Xinput[i] = lower_alpha[0];
                for (int j=0; j<26; j++)
                {
                    if (Xinput == line)
                    {
                        found = 1;
                        cout<<"\t\t"<<line<<endl;
                        break;
                    }
                    Xinput[i] = lower_alpha[j];
                }
                if (found == 1 ) break;
                else continue;
            }
        }
	}

    return found || (exchangedCharacters(input, root->left)) || (exchangedCharacters(input, root->right));
}

void exchangedCharacters (string input, Node *root, LinkedList<string> &ob)
{
    string line, Xinput;
    int found = 0;
    if(root==NULL){
    	return ;
	}
	else{
		line = root -> data;
	int len = input.size(), flen = line.size();
        if (len == flen)
        {
            for (int i = len-1; i >= 0 ; i--)
            {
                Xinput = input;
                Xinput[i] = lower_alpha[0];
                for (int j=0; j<26; j++)
                {
                    if (Xinput == line)
                    {
                        found = 1;
                        ob.insert(line);
                        break;
                    }
                    Xinput[i] = lower_alpha[j];
                }
                if (found == 1 ) break;
                else continue;
            }
        }
	}

    exchangedCharacters(input,root->left,ob);
    exchangedCharacters(input,root->right,ob);
}

//function to show correct spelling when there is a missing character in the given word.
int missingCharacter (string input, Node *root)
{
    string Xinput, line, Tinput, Tline, Xline;
    int found = 0;
	if(root == NULL)
	{
		return 0;
	}
	else
		{
		line = root->data;	
        for (int i = 0; i < 26; i++)
        {
            int len = input.size(), flen = line.size();
            Xinput = input;
            Xline = line;
            Xinput.resize(len+1,'a');
            Xinput[len] = lower_alpha[i];
            len = Xinput.size();
            string Ninput, Nline;
            if (len == flen)
            {
                for (int j = 1; j <=len; j++)
                    Ninput.push_back(Xinput[j]);
                for (int j = 1; j <= flen; j++)
                    Nline.push_back(Xline[j]);
                Xinput.resize(1);
                Xline.resize(1);
                sort(Nline.begin(),Nline.end());
                sort(Ninput.begin(),Ninput.end());
                Tinput = Xinput + Ninput;
                Tline = Xline + Nline;
                if (Tinput == Tline)
                {
                    found = 1;
                    cout<<"\t\t"<<line<<endl;
                    break;
                }
            }
        }
    }
    return found || (missingCharacter(input, root->left)) || (missingCharacter(input, root->right));
}

void missingCharacter (string input, Node *root, LinkedList<string> &ob)
{
    string Xinput, line, Tinput, Tline, Xline;
    int found = 0;
    
	if(root == NULL)
	{
		return;
	}
	else
		{
		line = root->data;	
        for (int i = 0; i < 26; i++)
        {
            int len = input.size(), flen = line.size();
            Xinput = input;
            Xline = line;
            Xinput.resize(len+1,'a');
            Xinput[len] = lower_alpha[i];
            len = Xinput.size();
            string Ninput, Nline;
            if (len == flen)
            {
                for (int j = 1; j <=len; j++)
                    Ninput.push_back(Xinput[j]);
                for (int j = 1; j <= flen; j++)
                    Nline.push_back(Xline[j]);
                Xinput.resize(1);
                Xline.resize(1);
                sort(Nline.begin(),Nline.end());
                sort(Ninput.begin(),Ninput.end());
                Tinput = Xinput + Ninput;
                Tline = Xline + Nline;
                if (Tinput == Tline)
                {
                    found = 1;
                    ob.insert(line);
                    break;
                }
            }
        }
    }

    missingCharacter(input, root->left, ob);
    missingCharacter(input, root->right, ob);
}

//function to show correct spelling of there is an extra character in given word.
int extraCharacter (string input, Node *root)
{
    string Xinput, line, Ninput, Tinput;
    int found = 0;
    if(root==NULL){
    	return 0;
	}
	else{
		line = root -> data;
		int len = input.size(), flen = line.size();
         if ((len-1) == flen)
         {
             for (int i = 1; i < len; i++)
             {
                 Xinput = input;
                 Xinput.erase(Xinput.begin()+i);
                 if (Xinput == line)
                 {
                     found = 1;
                     cout<<"\t\t"<<line<<endl;
                     break;
                 }

             }
         }
	}

    return found || (extraCharacter(input, root->left)) || (extraCharacter(input, root->right));
}

void extraCharacter (string input, Node *root, LinkedList<string> &ob)
{
    string Xinput, line, Ninput, Tinput;
    int found = 0;
    if(root==NULL){
    	return ;
	}
	else{
		line = root -> data;
		int len = input.size(), flen = line.size();
         if ((len-1) == flen)
         {
             for (int i = 1; i < len; i++)
             {
                 Xinput = input;
                 Xinput.erase(Xinput.begin()+i);
                 if (Xinput == line)
                 {
                     found = 1;
                     ob.insert(line);
                     break;
                 }

             }
         }
	}
             
	extraCharacter(input, root->left,ob);
	extraCharacter(input, root->right,ob);
}

//function to show right spelling when given word has wrong extra character and right one is missing.
int mixedExtraMissing (string input,Node *root)
{
    string Xinput, line, Xline;
    int found = 0;
    if(root==NULL){
    	return 0;
	}
	else{
		line = root -> data;
		int len = input.size(), flen = line.size();
        if (len == flen)
        {
            for (int i = 1; i < len; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    Xinput = input; Xline = line;
                    Xinput.erase(Xinput.begin()+i);
                    Xinput.resize(len, 'a');
                    Xinput[len-1] = lower_alpha[j];
                    sort(Xinput.begin()+1,Xinput.end());
                    sort(Xline.begin()+1,Xline.end());
                    if (Xinput == Xline)
                    {
                        found = 1;
                        cout<<"\t\t"<<line<<endl;
                        break;
                    }
                }
                if (found == 1) break;
            }
        }
	}
        
    return found || (mixedExtraMissing(input, root->left)) || (mixedExtraMissing(input, root->right));
}

void mixedExtraMissing (string input,Node *root, LinkedList<string> &ob)
{
    string Xinput, line, Xline;
    int found = 0;
    if(root==NULL){
    	return ;
	}
	else{
		line = root -> data;
		int len = input.size(), flen = line.size();
        if (len == flen)
        {
            for (int i = 1; i < len; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    Xinput = input; Xline = line;
                    Xinput.erase(Xinput.begin()+i);
                    Xinput.resize(len, 'a');
                    Xinput[len-1] = lower_alpha[j];
                    sort(Xinput.begin()+1,Xinput.end());
                    sort(Xline.begin()+1,Xline.end());
                    if (Xinput == Xline)
                    {
                        found = 1;
                        ob.insert(line);
                        break;
                    }
                }
                if (found == 1) break;
            }
        }
	}
        
  mixedExtraMissing(input, root->left, ob);
  mixedExtraMissing(input, root->right, ob);
}

void spellchecker(string input, LinkedList<string> &ob, Node *root)
{
    string line;
    BST temp;
    int len,flen,correct=0;
    
	len = input.length();
    
	for (int i=0; i < len; i++)
        input[i] = tolower(input[i]);
	
	if(temp.searchAvltree(root,input)==true)
	{
		return;
	}
	else
	{
		missingCharacter(input, root, ob);
		mixedExtraMissing(input,root,ob);
		extraCharacter(input,root,ob);
		exchangedCharacters(input,root,ob);
		incorrectArrangement(input,root,ob);
	}
}

void setConsoleColor(WORD c) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void loadingfunction(){
    cout<<"\n\n\n                L O A D I N G ..... ";
    cout<<"\n\n                ";
    for(int i=0 ; i<20;i++){
        Sleep(80);
        cout<<char(219);
    }
    cout << endl << endl << "\t\t";
    setConsoleColor(FOREGROUND_GREEN /*| BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED */);
	cout << "L o a d i n g   C o m p l e t e . . .";
	setConsoleColor( FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN/*BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED */);
	setConsoleColor(7);
    cout << endl << endl << "\t\t";
    system("pause");
	
}

int main()
{
	cout<<endl<<"\n\t\t-------------------------------";
	cout<<endl<<"\n\t\t| S P E L L   C H E C K K E R |";
	cout<<endl<<"\n\t\t-------------------------------";
	cout<<endl<<"\n\n\t\tATIF ALI  (21K-3340)\n\n\t\tBILAL AHMED  (21K-4864)\n\n\t\tMUHAMMAD  (21K-3192)";

    loadingfunction();
    
	BST ob;
	Node *root = NULL;
	ifstream inputFile("words.txt");
	
	string str="";
	int counter=0, option=0;
	while(!inputFile.eof())
	{
		inputFile >> str;
		root = ob.insert(root, str);
	}

	do{
		system("cls");
		cout<<"\n\n\t\tENTER 1 FOR WORD CORRECTION\n\t\tENTER 2 FOR PARAGRAPH CORRECTION\n\t\tENTER 0 TO EXIT"<<endl;
		cout<<" \n\n\t\t YOUR OPTION : ";
		cin>>option;
		
		if(option==0)
			break;
			
		if(option==1){
			
				string input,line;
        		int len,flen,correct=0;
        		cout<<"\n\t\tENTER THE WORD : "; 
        		fflush(stdin);
				getline(cin,input);
        
				len = input.length();
        
				for (int i=0; i < len; i++)
            		input[i] = tolower(input[i]);
		
				if(ob.searchAvltree(root,input)==true){
					cout<<"\n\t\tTHE SPELLING IS CORRECT !"<<endl;
				}
				else{
					int missing = 0, extra = 0, mixed = 0, incorrect = 0, exchanged = 0;
                	cout<<endl<<"\n\t\tSPELLING IS WRONG . POSSIBLE RIGHT SPELLINGS ARE GIVEN BELOW :  "<<endl<<endl;
                
					missing = missingCharacter(input, root);
					extra = extraCharacter(input, root);
                	mixed = mixedExtraMissing(input, root);
                	incorrect = incorrectArrangement(input,root);
                	exchanged = exchangedCharacters(input,root);
                
					if (missing == 0 && mixed == 0 && extra == 0 && incorrect == 0 && exchanged == 0)
                	{
                    	cout<<endl<<"\n\t\tNO SUCH WORD EXIST"<<endl;
                	}
				}
				cout << endl << endl << "\t\t";
				system("pause");
			}
				
			
			else if(option==2){
				cout << "\n\t\tENTER YOUR PARAGRAPH : ";
				fflush(stdin);
				getline(cin, str);
	
				stringstream ss(str);
				string temp;
				string corrected="";
				LinkedList<CorrectedWords> CWL;
	
				while(getline(ss, temp, ' '))
				{
					system("cls");
					LinkedList<string> LL;
					bool full_stop_present = 0;
		
					if(temp[temp.length()-1] == '.')
					{
						temp.pop_back();
						full_stop_present=1;
					}
		
					string check = CWL.searchMistake(temp);
					if(check != "N/A")
					{
						temp = check;
						if(full_stop_present == 1)
							temp.push_back('.');
						temp.push_back(' ');
						corrected = corrected + temp;
						continue;
					}
		
					CorrectedWords C;
					C.mistake = temp;
		
					spellchecker(temp, LL, root);
					cout <<"\n\t\tYOUR SENTENCE : "<< str << endl << endl;
					if(LL.head != NULL)
					{
						int choice=0;
						cout<<"\n\t\tYOUR MISTAKE : "<<temp;
						cout <<"\n\n\t\tDO YOU WANT TO IGNORE THE SPELLING MISTAKE ?:  (1 FOR YES, 0 FOR NO) ";
						cin >> choice;
						if(choice == 0)
						{
							int ans;
							int limit = LL.getLength();
						//	cout<<"\n\t\t";
							cout << endl << "\n\t\tTHESE ARE THE SUGGESTED MISTAKES ;\n";
							LL.print();
							 cout<<"\n\n\t\tENTER FOR WHICH NUMBER YOU WANT TO REPLACE: ";
							while(1)
							{
								cin >> ans;
								if (ans >= 1 && ans <= limit)
									break;
								cout << "/n/t/tINVALID SELECTION ! CHOOSE AGAIN ." << endl;
							}
							temp = LL.searchWord(ans);
							C.correction = temp;
							CWL.insert(C);
						}
					}
					else
					{
						if(ob.searchAvltree(root, temp) == false)
						{
							int ans2=0;
							cout << endl << temp << "\n\t\tDOESNOT EXIST. DO YOU WANT TO IGNORE OR REMOVE THIS WORD ? (1 FOR IGNORE, 0 FOR REMOVE) ";
							cin >> ans2;
							if(ans2 == 0)
								continue;
						}
					}
					if(full_stop_present == 1)
						temp.push_back('.');
					temp.push_back(' ');
					corrected = corrected + temp;
				}
	
				cout << "\n\t\tTHE CORRECTED PARA IS : "  << corrected<<endl;
	
				if(CWL.head != NULL)
				{
					cout << "\n\n\t\tYOUR MISTAKE HISTORY IS AS FOLLOWS : \n\n";
					cout << "\t\tMISTAKES\t:\tCORRECTIONS " << endl;
					CWL.print();
					cout << endl << endl << "\t\t";
					system("pause");
				}
			}
			else{
				cout<<"\n\t\tENTER CORRECT OPTION : "<<endl;
			}
		//	system("cls");	
	}while(option!=0);

    return 0;
}