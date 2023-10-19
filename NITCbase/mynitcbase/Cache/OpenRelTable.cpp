#include "OpenRelTable.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

OpenRelTable::OpenRelTable() {

  // initialize relCache and attrCache with nullptr
  for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    //relation cache and attribute cache are specialised
    //data structures used fo raccessing the catalogs.
    //these caches are both arrays of size 12 MAX_OPEN  
    //each entry in these array can store the catalog entries for a single relation
    AttrCacheTable::attrCache[i] = nullptr;
  }

  /************ Setting up Relation Cache entries ************/
  // (we need to populate relation cache with entries for the relation catalog
  //  and attribute catalog.)

  /**** setting up Relation Catalog relation in the Relation Cache Table****/
  RecBuffer relCatBlock(RELCAT_BLOCK);

  Attribute relCatRecord[RELCAT_NO_ATTRS];
  relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);

  struct RelCacheEntry relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block = RELCAT_BLOCK;
  relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[RELCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[RELCAT_RELID]) = relCacheEntry;

  /**** setting up Attribute Catalog relation in the Relation Cache Table ****/
  relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT);
  //struct RelCacheEntry  relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord,   &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block = RELCAT_BLOCK;
  relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_ATTRCAT;

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[ATTRCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[ATTRCAT_RELID]) = relCacheEntry;
  // set up the relation cache entry for the attribute catalog similarly
  // from the record at RELCAT_SLOTNUM_FOR_ATTRCAT
  // set the value at RelCacheTable::relCache[ATTRCAT_RELID]



  /************ Setting up Attribute cache entries ************/
  // (we need to populate attribute cache with entries for the relation catalog
  //  and attribute catalog.)

  /**** setting up Relation Catalog relation in the Attribute Cache Table ****/
  RecBuffer attrCatBlock(ATTRCAT_BLOCK);

  Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  attrCatBlock.getRecord(attrCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);

  AttrCacheEntry* attrCacheEntry = (struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
  attrCacheEntry->recId.block = ATTRCAT_BLOCK;
  attrCacheEntry->recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;
  AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry);
  attrCacheEntry->next=nullptr;
  //declare a pointer to preserver the head pointer
  struct AttrCacheEntry* ptr = attrCacheEntry ;
  //ptr=attrCacheEntry;

  

  // iterate through all the attributes of the relation catalog and create a linked
  // list of AttrCacheEntry (slots 0 to 5)
  // for each of the entries, set
  //    attrCacheEntry.recId.block = ATTRCAT_BLOCK;
  //    attrCacheEntry.recId.slot = i   (0 to 5)
  //    and attrCacheEntry.next appropriately
  // NOTE: allocate each entry dynamically using malloc
  for(int i=1;i<6;i++)
  {
    // ptr->next=(struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
    // Attribute attrCatRecord1[6];
    // attrCatBlock.getRecord(attrCatRecord1, i);
    // AttrCacheTable::recordToAttrCatEntry(attrCatRecord1, &ptr->next->attrCatEntry);
    // ptr=ptr->next;
    // ptr->recId.block=ATTRCAT_BLOCK;
    // ptr->recId.slot=i;
    // ptr->next=nullptr; 
    AttrCacheEntry* attrCacheEntry2 = (struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
    Attribute attrCatRecord1[6];
    attrCatBlock.getRecord(attrCatRecord1, i);
    AttrCacheTable::recordToAttrCatEntry(attrCatRecord1, &attrCacheEntry2->attrCatEntry);

    //cout << attrCatRecord1[1].sVal << "\n" ;
    attrCacheEntry2->recId.block=ATTRCAT_BLOCK;
    attrCacheEntry2->recId.slot=i;
    attrCacheEntry2->next=nullptr; 
    ptr->next = attrCacheEntry2 ;
    ptr = attrCacheEntry2;

  }
  // set the next field in the last entry to nullptr
  AttrCacheTable::attrCache[RELCAT_RELID] = (struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry)) ;
  *(AttrCacheTable::attrCache[RELCAT_RELID] )=  *attrCacheEntry;


  /**** setting up Attribute Catalog relation in the Attribute Cache Table ****/
  AttrCacheEntry* attrCacheEntry1 = (struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
  attrCacheEntry1->recId.block = ATTRCAT_BLOCK;
  attrCacheEntry1->recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;
  AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry1->attrCatEntry);
  attrCacheEntry1->next=nullptr;
  //declare a pointer to preserver the head pointer
  struct AttrCacheEntry* ptr1 = (struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
  ptr1=attrCacheEntry1;

  

  // iterate through all the attributes of the relation catalog and create a linked
  // list of AttrCacheEntry (slots 0 to 5)
  // for each of the entries, set
  //    attrCacheEntry.recId.block = ATTRCAT_BLOCK;
  //    attrCacheEntry.recId.slot = i   (0 to 5)
  //    and attrCacheEntry.next appropriately
  // NOTE: allocate each entry dynamically using malloc
  for(int i=6;i<12;i++)
  {
    // ptr1->next=(struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
    // Attribute attrCatRecord1[6];
    // attrCatBlock.getRecord(attrCatRecord1, i);
    // AttrCacheTable::recordToAttrCatEntry(attrCatRecord1, &ptr1->next->attrCatEntry);
    // ptr1=ptr1->next;
    // ptr1->recId.block=ATTRCAT_BLOCK;
    // ptr1->recId.slot=i;
    // ptr1->next=nullptr; 

    AttrCacheEntry* attrCacheEntry2 = (struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
    Attribute attrCatRecord1[6];
    attrCatBlock.getRecord(attrCatRecord1, i);
    AttrCacheTable::recordToAttrCatEntry(attrCatRecord1, &attrCacheEntry2->attrCatEntry);

    //cout << attrCatRecord1[1].sVal << "\n" ;
    attrCacheEntry2->recId.block=ATTRCAT_BLOCK;
    attrCacheEntry2->recId.slot=i;
    attrCacheEntry2->next=nullptr; 
    ptr1->next = attrCacheEntry2 ;
    ptr1 = attrCacheEntry2;
  }

  // set up the attributes of the attribute cache similarly.
  // read slots 6-11 from attrCatBlock and initialise recId appropriately

  // set the value at AttrCacheTable::attrCache[ATTRCAT_RELID]
  AttrCacheTable::attrCache[ATTRCAT_RELID] = (struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry)) ;
  *(AttrCacheTable::attrCache[ATTRCAT_RELID]) = *attrCacheEntry1;
}


OpenRelTable::~OpenRelTable() {
  // free all the memory that you allocated in the constructor
  // for(int i=0;i<2;i++)
  // {
  //   free(RelCacheTable::relCache[i]);
  //   free(AttrCacheTable::attrCache[i]);
  // }

  free(RelCacheTable::relCache[RELCAT_RELID]);
  free(RelCacheTable::relCache[ATTRCAT_RELID]);
  free(AttrCacheTable::attrCache[RELCAT_RELID]);
  free(AttrCacheTable::attrCache[ATTRCAT_RELID]);
  
}