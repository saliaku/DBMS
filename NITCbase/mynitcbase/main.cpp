#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>
#include <cstring>

// initial int main()
// int main(int argc, char *argv[]) {
//   /* Initialize the Run Copy of Disk */
//   Disk disk_run;
//   // StaticBuffer buffer;
//   // OpenRelTable cache;

//   return FrontendInterface::handleFrontend(argc, argv);
// }

//stage 1
// int main(int argc, char *argv[]) {
//   Disk disk_run;

//   unsigned char buffer[BLOCK_SIZE];
//   Disk::readBlock(buffer , 8191);
//   char message[]="hello world";

//   memcpy(buffer, message,12);
//   Disk::writeBlock(buffer , 8191);

//   unsigned char buffer2[12];
//   char message2[11];
//   Disk::readBlock(buffer2, 8191);
//   memcpy(message2, buffer2,12);
  
//   std::cout << message2<<" ";
//   // for(int i=20;i<22;i++)
//   // {
//   //   std::cout<<buffer2[i];
//   // }
//   // std::cout<<"\n";
//   // std::cout<<message;
//   return 0;
// }

//stage 1 exercise q1
// int main(int argc, char *argv[]) {
//   /* Initialize the Run Copy of Disk */
//   Disk disk_run;
  
//   unsigned char buffer2[BLOCK_SIZE];
//   char message2[6];

//   Disk::readBlock(buffer2,0);
//   memcpy(message2,buffer2,6);
//   for(int i=0;i<6;i++)
//   {
//     std::cout<<(int)message2[i]<<" ";
//   }
//   //std::cout<<endl;

//   return 0;
// }

//stage 2
int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

  // create objects for the relation catalog and attribute catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;
  HeadInfo attrCatHeader;

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
  attrCatBuffer.getHeader(&attrCatHeader);
  // for (int i = 0; i<relCatHeader.numEntries; i++) {

  //   Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

  //   relCatBuffer.getRecord(relCatRecord, i);

  //   printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

  //   for (int j = 0; j<attrCatHeader.numEntries; j++) {
  //     Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  //     attrCatBuffer.getRecord(attrCatRecord, j);
  //     // declare attrCatRecord and load the attribute catalog entry into it

  //     if (/* attribute catalog entry corresponds to the current relation */strcmp(relCatRecord[RELCAT_REL_NAME_INDEX].sVal, attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal)==0) {
  //       const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
  //       printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal/* get the attribute name */, attrType);
  //     }
  //   }
  //   printf("\n");
  // }

  /*
  for i = 0 and i = 1 (i.e RELCAT_RELID and ATTRCAT_RELID)

      get the relation catalog entry using RelCacheTable::getRelCatEntry()
      printf("Relation: %s\n", relname);

      for j = 0 to numAttrs of the relation - 1
          get the attribute catalog entry for (rel-id i, attribute offset j)
           in attrCatEntry using AttrCacheTable::getAttrCatEntry()

          printf("  %s: %s\n", attrName, attrType);
  */

  return 0;
}
