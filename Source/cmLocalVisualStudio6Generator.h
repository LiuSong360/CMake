/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef cmLocalVisualStudio6Generator_h
#define cmLocalVisualStudio6Generator_h

#include "cmLocalGenerator.h"

class cmMakeDepend;
class cmTarget;
class cmSourceFile;

// please remove me.... Yuck
#include "cmSourceGroup.h"

/** \class cmLocalVisualStudio6Generator
 * \brief Write a LocalUnix makefiles.
 *
 * cmLocalVisualStudio6Generator produces a LocalUnix makefile from its
 * member m_Makefile.
 */
class cmLocalVisualStudio6Generator : public cmLocalGenerator
{
public:
  ///! Set cache only and recurse to false by default.
  cmLocalVisualStudio6Generator();

  virtual ~cmLocalVisualStudio6Generator();
  
  /**
   * Generate the makefile for this directory. fromTheTop indicates if this
   * is being invoked as part of a global Generate or specific to this
   * directory. The difference is that when done from the Top we might skip
   * some steps to save time, such as dependency generation for the
   * makefiles. This is done by a direct invocation from make. 
   */
  virtual void Generate(bool fromTheTop);

  void OutputDSPFile();

  enum BuildType {STATIC_LIBRARY, DLL, EXECUTABLE, WIN32_EXECUTABLE, UTILITY};

  /**
   * Specify the type of the build: static, dll, or executable.
   */
  void SetBuildType(BuildType,const char *name);

  /**
   * Return array of created DSP names in a STL vector.
   * Each executable must have its own dsp.
   */
  std::vector<std::string> GetCreatedProjectNames() 
    {
    return m_CreatedProjectNames;
    }

private:
  std::string m_DSPHeaderTemplate;
  std::string m_DSPFooterTemplate;
  std::vector<std::string> m_CreatedProjectNames;
  
  void CreateSingleDSP(const char *lname, cmTarget &tgt);
  void WriteDSPFile(std::ostream& fout, const char *libName, 
                    cmTarget &tgt);
  void WriteDSPBeginGroup(std::ostream& fout, 
			  const char* group,
			  const char* filter);
  void WriteDSPEndGroup(std::ostream& fout);

  void WriteDSPHeader(std::ostream& fout, const char *libName,
                      const cmTarget &tgt, std::vector<cmSourceGroup> &sgs);

  void WriteDSPFooter(std::ostream& fout);
  void AddDSPBuildRule(cmSourceGroup&);
  void WriteCustomRule(std::ostream& fout,
                       const char* source,
                       const char* command,
                       const std::set<std::string>& depends,
                       const std::set<std::string>& outputs,
                       const char* flags);

  std::string CreateTargetRules(const cmTarget &target, 
                                const char *libName);
  std::string CombineCommands(const cmSourceGroup::Commands &commands,
                              cmSourceGroup::CommandFiles &totalCommand,
                              const char *source);

  std::string m_IncludeOptions;
  std::vector<std::string> m_Configurations;
};

#endif

