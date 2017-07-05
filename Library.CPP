/*
 TOOK HELP FROM THE BOOK"COMPUTER SCIENCE WITH C++" BY SUMITRA ARORA

 This program allows you to issue a book of your choice
 1.you can create a student record
 2.you can create a book record,assuming that the book you create is in the
   library
 3.you can delete the book or student record
 4.you can see the student and book record list
 5.you can issue only one book at a time only after creating a record of book
   and student
 6.you must return a book in 20 days, or else you wil have to pay a fine of$1
   each following day
 */

//headerfiles needed
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<iomanip.h>
#include<ctype.h>
#include<stdio.h>
#include<process.h>
class book
{char book_name[50],author_name[50];
 int book_no;

 public:
 void create_book()
 {cout<<"Enter book number\n";
  cin>>book_no;
  cout<<"Enter the name of the book\n";
  gets(book_name);
  cout<<"Enter the name of the author\n";
  gets(author_name);
 }

 void print_book()
 {cout<<"Book number: "<<book_no<<"\n";
  cout<<"Book name: "<<book_name<<"\n";
  cout<<"Author name: "<<author_name<<"\n";
 }

 int getBook_no()
 {return book_no;
 }

 void report()
 {cout<<setw(6)<<book_no<<setw(25)<<book_name<<setw(25)<<author_name<<"\n";
 }
};

class student
{char name[20];
 long std_no;
 int ino,stbno;
 //ino is the number of books issued by the student
 //stbno is the book number issued by the student
 public:
 void create_student()
 {clrscr();
  cout<<"Enter your student no. after V00\n";
  cin>>std_no;
  cout<<"enter the name of the student\n";
  gets(name);
  ino=0;
  stbno=0;
 }

 void print_student()
 {cout<<"Student number: V00"<<std_no<<"\n";
  cout<<"Student name: "<<name<<"\n";
  cout<<"Number of books issued: "<<ino<<"\n";
  if(ino==1)
  {cout<<"Book number: "<<stbno<<"\n";
  }
 }

 long getStd_no()
 {return std_no;
 }

 int getStbno()
 {return stbno;
 }

 int getIno()
 {return ino;
 }

 void addIno()
 {ino=1;
 }

 void resetIno()
 {ino=0;
 }

 void retStbno(int t)
 {stbno=t;
 }
 void report()
 {cout<<setw(6)<<"V00"<<std_no<<setw(25)<<name<<setw(22)<<ino<<"\n";
 }
};
//global variables
fstream f1,f2;
book bk;
student st;

void create_book();
void create_student();
void del_student();
void del_book();
void book_issue();
void book_deposit();
void display_alls();
void display_allb();

void main()
{char ch;
 do
 {clrscr();
  cout<<"*****************************************\n";
  cout<<"    Simple Library Management System   \n";
  cout<<"*****************************************\n";
  cout<<"    1.create student record \n";
  cout<<"    2.display student record \n";
  cout<<"    3.delete student record \n";
  cout<<"    4.create book \n";
  cout<<"    5.display book \n";
  cout<<"    6.delete book \n";
  cout<<"    7.book issue \n";
  cout<<"    8.book deposit \n";
  cout<<"    9.exit \n";
  cout<<"\n";
  cout<<"Enter choice \n";
  cin>>ch;
  switch(ch)
  {case '1':create_student();
	       break;
   case '2':display_alls();
	       break;
   case '3':del_student();
	       break;
   case '4':create_book();
	       break;
   case '5':display_allb();
	       break;
   case '6':del_book();
	       break;
   case '7':book_issue();
	       break;
   case '8':book_deposit();
	       break;
   case '9':exit(0);
  }
 }
 while(ch!=9);
}

//function to create book
void create_book()
{clrscr();
 f1.open("book.dat",ios::out|ios::app|ios::binary);
 bk.create_book();
 f1.write((char*)&bk,sizeof(book));
 f1.close();
 cout<<"\n";
 cout<<"record created\n";
 getch();
}

//function to create student record
void create_student()
{clrscr();
 f1.open("student.dat",ios::out|ios::app|ios::binary);
 st.create_student();
 f1.write((char*)&st,sizeof(student));
 f1.close();
 cout<<"\n";
 cout<<"record created\n";
 getch();
}

//fuction to delete book
void del_book()
{int n,t=0;
 clrscr();
 cout<<"Enter the book no. to delete\n";
 cin>>n;
 f1.open("book.dat",ios::binary|ios::in);
 fstream f2;
 f2.open("temp.dat",ios::binary|ios::out);
 f1.seekg(0,ios::beg);
 while(f1.read((char*)&bk,sizeof(book)))
 {if(bk.getBook_no()!=n)
   //writing all the book records except the one to be deleted
   f2.write((char*)&bk,sizeof(book));
  else
   t=1;
 }
 f2.close();
 f1.close();
 remove("book.dat");
 rename("temp.dat","book.dat");
 if(t==1)
  cout<<"book record deleted\n";
 else
 cout<<"record not found\n";
 getch();
}

//fuction to delete student record
void del_student()
{long n;
 int t=0;
 clrscr();
 cout<<"Enter the student no. to delete: V00";
 cin>>n;
 f1.open("student.dat",ios::binary|ios::in);
 fstream f2;
 f2.open("temp.dat",ios::binary|ios::out);
 f1.seekg(0,ios::beg);
 while(f1.read((char*)&st,sizeof(student)))
 {if(st.getStd_no()!=n)
   //writing all the student records except the one to be deleted
   f2.write((char*)&st,sizeof(student));
  else
   t=1;
 }
 f2.close();
 f1.close();
 remove("student.dat");
 rename("temp.dat","student.dat");
 if(t==1)
  cout<<"student record deleted\n";
 else
  cout<<"record not found\n";
 getch();
}

//book list
void display_allb()
{clrscr();
 f1.open("book.dat",ios::binary|ios::in);
 if(!f1)
 {cout<<"file cannot open\n";
 }
 cout<<"book list\n";
 cout<<"   book no.               name               author's name\n";
 while(f1.read((char*)&bk,sizeof(book)))
 {bk.report();
 }
 f1.close();
 getch();
}

//student list
void display_alls()
{clrscr();
 f1.open("student.dat",ios::binary|ios::in);
 if(!f1)
 {cout<<"file cannot open\n";
 }
 cout<<"student record list\n";
 cout<<"   student no.                  name                 book issued\n";
 while(f1.read((char*)&st,sizeof(student)))
 {st.report();
 }
 f1.close();
 getch();
}

//issue book
void book_issue()
{long sn;int bn;
 int f=0,t=0;
 clrscr();
 cout<<"enter student no.: V00";
 cin>>sn;
 f1.open("student.dat",ios::in|ios::binary|ios::out);
 f2.open("book.dat",ios::in|ios::out|ios::binary);
 while(f1.read((char*)&st,sizeof(student)) && f==0)
 {if(st.getStd_no()==sn)
  {f=1;
   if(st.getIno()==0)
    {cout<<"enter book no.\n";
     cin>>bn;
     while(f2.read((char*)&bk,sizeof(book)) && t==0)
      {if(bk.getBook_no()==bn)
	{bk.print_book();
	 t=1;
	 st.addIno();
	 st.retStbno(bk.getBook_no());
	 int pos=-1*sizeof(st);
	 f1.seekp(pos,ios::cur);
	 f1.write((char*)&st,sizeof(student));
	 cout<<"\nSubmit the book in 20 days else fine $1 for each day\n";
	}
       }
       if(t==0)
	cout<<"record not found\n";
      }
      else
      cout<<"you have not returned last book\n";
   }
 }
 if(f==0)
  cout<<"student record not found\n";
 getch();
 f1.close();
 f2.close();
}

//deposit a book
void book_deposit()
{int bn,f=0,t=0,day,fine;
 long sn;
 clrscr();
 cout<<"enter student no. :V00";
 cin>>sn;
 f1.open("student.dat",ios::in|ios::binary|ios::out);
 f2.open("book.dat",ios::in|ios::out|ios::binary);
 while(f1.read((char*)&st,sizeof(student)) && f==0)
 {if(st.getStd_no()==sn)
  {f=1;
   if(st.getIno()==1)
    {while(f2.read((char*)&bk,sizeof(book)) && t==0)
     {if(bk.getBook_no()==st.getStbno())
      {bk.print_book();
       t=1;
       cout<<"Enter total no. of days you borrowed the book\n";
       cin>>day;
       if(day>20)
	{fine=day-20;
	 cout<<"fine to be deposited: $"<<fine<<"\n";
	}
       st.resetIno();
       int pos=-1*sizeof(st);
       f1.seekp(pos,ios::cur);
       f1.write((char*)&st,sizeof(student));
       cout<<"book deposited\n";
      }
     }
     if(t==0)
     cout<<"book not found\n";
    }
    else
      cout<<"no book issued\n";
   }
  }
  if(f==0)
    cout<<"student record does not exists\n";
  getch();
  f1.close();
  f2.close();
 }
