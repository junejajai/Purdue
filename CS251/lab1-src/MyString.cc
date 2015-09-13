
// CS251 Data Structures
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include<new>
#include "MyString.h"

// My own implementation of strlen
int
MyString::slength(const char *s) const
{
	char * hold = (char *)s;
	int count = 0;
	// Add implementation here

	while(*hold !='\0')
	{
		count++;
		hold++;		
	}
	return count;
}

// Initialize _s. Allocate memory for _s and copy s into _s
	void
MyString::initialize(const char * s)
{
	// Add implementation here
	// Allocate memory for _s.
	_s = new char[slength(s)+1] ; //(char *)malloc(sizeof(s));
	// Copy s into _s
	char * t = _s;
	while(*s != '\0')
	{
		*t = *s;
		t++;
		s++;
	}	
}

// Create a MyString from a C string
MyString::MyString(const char * s)
{
	initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
	initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
	_s = new char[1];
	*_s = 0;
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
	if (this != &other) // protect against invalid self-assignment
	{
		// deallocate old memory
		delete [] _s;

		// Initialize _s with the "other" object.
		initialize(other._s);

		// by convention, always return *this
		return *this;
	}
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
	MyString
MyString::substring(int i, int n)
{
	// Add implementation here
	if(i>slength(_s))
	{
		MyString *sub = new MyString();
		return *sub;
	}

	// Make sure that i is not beyond the end of string
	//if((i+n)>slength(_s))
	//{
	//MyString *sub = new MyString();
	//return *sub;
	//	}
	// Allocate memory for substring
	char * s = new char[n+1];
	char * t = _s;
	char * temp = s;	
	t = t + i;
	int c = 0;
	while(*t!='\0')
	{
		if(c < n)
		{
			*temp = *t;
			t++;
			c++;
			temp++;
		}
		else
		{	
			//*temp='\0';
			break;
		}
	}
	*temp = '\0';
	// Copy characters of substring

	MyString sub;
	sub = MyString(s);
	// Return substring
	return sub;
	/*
	   if (i > length())
	   {
	   return MyString();
	   }
	   char *_sub;
	   _sub = new char[n + 1];
	   int j;
	   for (j = 0; j < n; j++)
	   {
	   _sub[j] = _s[i+j];
	   }
	   _sub[n] = '\0';
	   MyString sub;
	   sub = MyString(_sub);
	   return sub;

*/
}

// Remove at most n chars starting at location i
	void
MyString::remove(int i, int n)
{
	// Add implementation here

	// If i is beyond the end of string return
	if(i>slength(_s))
	{
		return;
	}
	// If i+n is beyond the end trunc string
	if((i + n) > slength(_s))
	{
		return;
	}
	// Remove characters
	char * t = _s;
	char * temp = new char[slength(_s)];//(char *)malloc(slength(_s)*sizeof(char));	
	char * l = temp;	
	int c = 0;	
	while(c < i)
	{
		*l=*t;
		t++;
		l++;
		c++;
	}
	t = t + n;
	while(*t!='\0')
	{
		*l=*t;
		t++;
		l++;
	}
	*l = '\0';
	_s = temp;
	//for(int i = 0;i<n;i++)
	//{
	//for()
	//}
}

// Return true if strings "this" and s are equal
	bool
MyString::operator == (const MyString & s)
{
	int i = 0;
	while((_s[i]!='\0' && s._s[i]!='\0')&&(_s[i]==s._s[i]))
	{
		i++;
	}
	return ((_s[i]-s._s[i])==0);
	// Add implementation here
}


// Return true if strings "this" and s are not equal
	bool
MyString::operator != (const MyString &s)
{
	// Add implementation here
	int i = 0;
	while((_s[i]!='\0' && s._s[i]!='\0')&&(_s[i]==s._s[i]))
	{
		i++;
	}
	return ((_s[i]-s._s[i])!=0);
}

// Return true if string "this" and s is less or equal
	bool
MyString::operator <= (const MyString &s)
{
	// Add implementation here
	int i = 0;
	while((_s[i]!='\0' && s._s[i]!='\0')&&(_s[i]==s._s[i]))
	{
		i++;
	}
	return ((_s[i]-s._s[i])<=0);
}

// Return true if string "this" is greater than s
	bool
MyString::operator > (const MyString &s)
{
	// Add implementation here
	int i = 0;
	while((_s[i]!='\0' && s._s[i]!='\0')&&(_s[i]==s._s[i]))
	{
		i++;
	}
	return ((_s[i]-s._s[i])>0);
}

// Return character at position i.  Return '\0' if out of bounds.
	char
MyString::operator [] (int i)
{
	// Add implementation here
	if(i>slength(_s))
	{
		return '\0';
	}

	return _s[i];
}

// Return C representation of string
	const char *
MyString::cStr()
{
	// Add implementation here
	return _s;
}

// Get string length of this string.
int
MyString::length() const
{
	// Add implementation here
	return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
	// Add implementation here
	delete [] _s;
}

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
	// Add implementation here

	// Allocate memory for the concatenated string
	int size = s1.length() + s2.length() + 1;
	// Add s1


	// Add s2

	MyString s;
	s._s = new char[size];
	char * h1 = s1._s;
	char * h2 = s2._s;
	char * temp = s._s;
	while(*h1!='\0')
	{
		*temp=*h1;
		h1++;
		temp++;			
	}
	while(*h2!='\0')
	{
		*temp=*h2;
		h2++;
		temp++;	
	}
	*temp = '\0';

	return s;
}

