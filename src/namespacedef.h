/******************************************************************************
 *
 * 
 *
 * Copyright (C) 1997-2001 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#ifndef NAMESPACEDEF_H
#define NAMESPACEDEF_H

#include "qtbc.h"
#include <qstrlist.h>
#include <qdict.h>
#include "definition.h"
#include "memberlist.h"

class ClassDef;
class OutputList;
class ClassList;
class ClassDict;
class MemberDef;
class NamespaceList;
class MemberGroupDict;
class MemberGroupList;

class NamespaceDef : public Definition
{
  public:
    NamespaceDef(const char *defFileName,int defLine,
                 const char *name,const char *ref=0);
   ~NamespaceDef();
    DefType definitionType() { return TypeNamespace; }
    QCString getOutputFileBase() const { return fileName; }
    void insertUsedFile(const char *fname);
    void writeDocumentation(OutputList &ol);
    void insertClass(ClassDef *cd);
    void insertMember(MemberDef *md);
    void computeAnchors();
    int countMembers();
    void addUsingDirective(NamespaceDef *nd);
    NamespaceList *getUsedNamespaces() const { return usingDirList; }
    void addUsingDeclaration(ClassDef *cd);
    ClassList *getUsedClasses() const { return usingDeclList; }
    
    bool isLinkableInProject()
    {
      int i = name().findRev("::");
      if (i==-1) i=0; else i+=2;
      return !name().isEmpty() && name().at(i)!='@' &&
              hasDocumentation() && !isReference();
    }
    bool isLinkable()
    {
      return isLinkableInProject() || isReference();
    }
    void addMembersToMemberGroup();
    void distributeMemberGroupDocumentation();
    
  protected:
    void addMemberListToGroup(MemberList *,bool (MemberDef::*)() const);

  private:
    //QCString reference;
    QCString fileName;
    QStrList files;
    ClassList *classList;
    ClassDict *classDict;
    NamespaceList *usingDirList;
    ClassList *usingDeclList;

    MemberList allMemberList;
    MemberList defineMembers;
    MemberList protoMembers;
    MemberList typedefMembers;
    MemberList enumMembers;
    MemberList enumValMembers;
    MemberList funcMembers;
    MemberList varMembers;

    /* user defined member groups */
    MemberGroupList    *memberGroupList;
    MemberGroupDict    *memberGroupDict;
};

class NamespaceList : public QList<NamespaceDef>
{ 
  public:
   ~NamespaceList() {}
    int compareItems(GCI item1,GCI item2)
    {
      return stricmp(((NamespaceDef *)item1)->name(),
                    ((NamespaceDef *)item2)->name()
                   );
    }
};

class NamespaceListIterator : public QListIterator<NamespaceDef>
{
  public:
    NamespaceListIterator(const NamespaceList &l) : 
      QListIterator<NamespaceDef>(l) {}
};

class NamespaceDict : public QDict<NamespaceDef>
{
  public:
    NamespaceDict(int size) : QDict<NamespaceDef>(size) {}
   ~NamespaceDict() {}
};

#endif
