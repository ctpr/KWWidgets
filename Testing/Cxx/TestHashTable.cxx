#include "vtkKWHashTable.h"
#include "vtkKWHashTableIterator.h"
#include <iostream.h>

int main()
{
  int res = 0;
  int cc;
  char names[][10] = {
    "Andy",
    "Amy",
    "Berk",
    "Bill",
    "Brad",
    "Charles",
    "Dina",
    "Ken",
    "Lisa",
    "Sebastien",
    "Will"
  };

  cout << "Testing KW Hash Table" << endl;

  vtkKWHashTable *ht = vtkKWHashTable::New();

  for ( cc =0 ; cc< 10; cc++ )
    {
    unsigned long key = vtkKWHashTable::HashString( names[cc] );
    int res = ht->Insert( names[cc], (void *)names[cc] );
    cout << "Insert: " << names[cc] << " at key: " << key 
	 << (res ? " ok" : " problem") << endl;
    }

  for ( cc =0 ; cc< 10; cc++ )
    {
    unsigned long key = vtkKWHashTable::HashString( names[cc] );
    char *name = ( char * )ht->Lookup( names[cc] );
    if ( name ) 
      {
      cout << key << ": " << name << endl;
      }
    else
      {
      cout << key << ": does not exist" << endl;
      }
    }

  for ( cc=0; cc<10; cc++ )
    {
    ht->Remove( names[cc] );
    }

  for ( cc=0; cc<10; cc++) 
    {
    unsigned long key = vtkKWHashTable::HashString( names[cc] );
    int res = ht->Insert( names[cc], (void *)names[cc] );
    cout << "Insert: " << names[cc] << " at key: " << key 
	 << (res ? " ok" : " problem") << endl;
    }

  vtkKWHashTableIterator *it = ht->Iterator();
  cout << "Traverse hash table:" << endl;
  if ( !it )
    {
    cout << "Cannot get the pointer. This is strange, since I just"
      "inserted something..." << endl;
    res = 1;
    }
  while ( it )
    {
    if ( it->Valid() )
      {      
      unsigned long key = it->GetKey();
      void *value = it->GetData();
      cout << "Key: " << key << " store element: " << value 
	   << " (" << static_cast<char *>(value) << ")" << endl;
      }
    if ( !it->Next() )
      {
      break;
      }
    }
  if ( it )
    {
    it->Delete();
    }

  ht->Delete();

  return res;
}

