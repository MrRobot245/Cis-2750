/*
* ------------------------------------------------------------------
*  JNICALLS.c - Wrapper for C code to generate GUI's dynamically
*
*  CIS*2750 - Software Systems Development and Integration
*  School of Computer Science
*  University of Guelph
*  Author: Nathan Reymer
* ------------------------------------------------------------------
*/

#include <jni.h>
#include <stdio.h>
#include "../Dialogc.h"
#include "ParameterManager.h"
//Global paramaters to make it easier
ParameterManager *params;
ParameterList *fields;
ParameterList *buttons;
char *guiFields[100][100];
char *guiButts[100][100];
char * ftypes[100][100];
char * btypes[100][100];

//Creates the LL and adds the manditory items
JNIEXPORT void JNICALL Java_Dialogc_DialogcCreate(JNIEnv *env, jobject obj, jint size)
{

	//Destroy somewhere
	params = PM_create(size);
	PM_manage(params,"title",STRING_TYPE,1);
	PM_manage(params,"fields",LIST_TYPE,1);
	PM_manage(params,"buttons",LIST_TYPE,1);

}

//Parse the file
JNIEXPORT int JNICALL Java_Dialogc_DialogcParse(JNIEnv * env, jobject obj, jstring filePath)
{
	int rVal=0;
	const char *str = (*env)->GetStringUTFChars(env,filePath,NULL);
	FILE *fp=fopen(str,"r");
	rVal=PM_parseFrom(params,fp,'#');
	fclose(fp);
	return rVal;
}

//After parsing, look at all the fields and manage, add all values
JNIEXPORT void JNICALL Java_Dialogc_DialogcManage (JNIEnv * env, jobject job){
	char * value;
	ParameterManager *PM=params;
	fields = PM_getValue(params,"fields").list_val;
	buttons = PM_getValue(params,"buttons").list_val;
	while(value = PL_next(fields))
	{

		PM_manage(params,value,NO_TYPE,1);

	}
	while(value = PL_next(buttons))
	{
		PM_manage(params,value,NO_TYPE,1);
	}
}

//Set the values of the title and buttons into the array
JNIEXPORT void JNICALL Java_Dialogc_DialogcPeek(JNIEnv *env, jobject job)
{
	ParameterManager *PM=params;
	char *title;
	char * value;
	int i=0;
	fields = PM_getValue(params,"fields").list_val;
	buttons = PM_getValue(params,"buttons").list_val;
	for(int i=0;i<100;i++)
	{
		guiFields[i][0]=NULL;
		guiButts[i][0]=NULL;
		ftypes[i][i]=NULL;
		btypes[i][i]=NULL;
	}
	while(value = PL_next(fields))
	{
		PM=params;
		while(PM!=NULL)
		{ //Check the name, then set the value
			if((strcmp(value,PM->pName) == 0))
			{
				if(PM->type==1)
				{
					ftypes[i][0]="int";
				}
				if(PM->type==2)
				{
					ftypes[i][0]="double";
				}
				if(PM->type==5)
				{
					ftypes[i][0]="String";
				}
			}
			PM = PM->next;
		}
		guiFields[i][0]=value;
		i++;
	}

	for(int q=0;q<i;q++)
	{

		title = PM_getValue(params,guiFields[q][0]).str_val;
	}
	i=0;

	while(value = PL_next(buttons))
	{
		PM=params;
		while(PM!=NULL)
		{ //Check the name, then set the value
			if((strcmp(value,PM->pName) == 0))
			{
				btypes[i][0]="QueryListener";
			}
			PM = PM->next;
		}

		guiButts[i][0]=value;
		i++;
	}
	for(int q=0;q<i;q++)
	{
		title = PM_getValue(params,guiButts[q][0]).str_val;
	}
}

//Write the custom GUI based on for loops
JNIEXPORT void JNICALL Java_Dialogc_DialogcWrite(JNIEnv * env, jobject obj, jstring filePath, jstring dir)
{
	int lastField=0;
	char * title=PM_getValue(params,"title").str_val;
	const char *wDir = (*env)->GetStringUTFChars(env,dir,NULL);
	char *path=(char *)malloc(sizeof(char)*100);
	strcpy(path,wDir);
	strcat(path,"/");

	//Changes the space so the compiler doesnt cry
	for(int i=0;i<strlen(title);i++)
	{
		if(title[i]==' ')
		title[i]='_';
	}
	//strcat(path,"FieldEdit");
	strcat(path,title);
	strcat(path,".java");
	FILE *fp=fopen(path,"w");


	fprintf(fp,"import java.awt.*;\n");
	fprintf(fp,"import java.io.*;\n");
	fprintf(fp,"import java.nio.*;\n");
	fprintf(fp,"import java.util.*;\n");
	fprintf(fp,"import javax.swing.*;\n");
	fprintf(fp,"import java.awt.event.ActionEvent;\n");
	fprintf(fp,"import java.awt.event.ActionListener;\n");


	fprintf(fp,"public class %s extends JFrame implements ActionListener\n",title);
	fprintf(fp,"{\npublic %s()\n{\n\tguiUI();\n}\n",title);
	fprintf(fp,"\tJTextArea editArea = new JTextArea(6, 20);\n");
	for(int i=0;i<100;i++)
	{
		if(guiFields[i][0]!=NULL)
		{

			fprintf(fp,"\tJLabel %sLbl= new JLabel(\"%s\");\n",guiFields[i][0],guiFields[i][0]);
			fprintf(fp,"\tJTextField %stField= new JTextField();\n",guiFields[i][0]);
		}
	}

	fprintf(fp,"private void guiUI()\n{\n");

	//Add Labels and text fields
	for(int i=0;i<100;i++)
	{
		if(guiFields[i][0]!=NULL)
		{

			fprintf(fp,"\t%sLbl.setBounds(30, %d, 150, 80);\n",guiFields[i][0],40+(i*30));
			fprintf(fp,"\t%stField.setBounds(180, %d, 300, 20);\n",guiFields[i][0],75+(i*30));
			lastField=75+(i*30)+50;
		}
	}
	//Add buttons and listeners
	for(int i=0;i<100;i++)
	{
		if(guiButts[i][0]!=NULL)
		{
			fprintf(fp,"\tJButton %sButton= new JButton(\"%s\");\n",guiButts[i][0],guiButts[i][0]);
			fprintf(fp,"\t%sButton.setBounds(%d,%d,90,40);\n",guiButts[i][0],60+(i*100),lastField);
			fprintf(fp,"\t%sButton.addActionListener(this);\n",guiButts[i][0]);
		}
	}
	for(int i=0;i<strlen(title);i++)
	{
		if(title[i]=='_')
		title[i]=' ';
	}
	fprintf(fp,"\tJFrame frame= new JFrame(\"%s\");\n\n",title);
	for(int i=0;i<strlen(title);i++)
	{
		if(title[i]==' ')
		title[i]='_';
	}
	fprintf(fp,"JScrollPane scrollingArea = new JScrollPane(editArea);\n");
	fprintf(fp,"JPanel editorWindow = new JPanel();\n");
	fprintf(fp,"editorWindow.setBounds(0,300,600,250);\n");
	fprintf(fp,"editorWindow.setLayout(new BorderLayout());\n");
	fprintf(fp,"editorWindow.add(scrollingArea, BorderLayout.SOUTH);\n");
	fprintf(fp,"frame.setLayout(null);\n\n");

	//Add labels and fields to the frame
	for(int i=0;i<100;i++)
	{
		if(guiFields[i][0]!=NULL)
		{
			fprintf(fp,"\tframe.add(%sLbl);\n",guiFields[i][0]);
			fprintf(fp,"\tframe.add(%stField);\n",guiFields[i][0]);
		}
	}
	//Add the buttons to the frame
	for(int i=0;i<100;i++)
	{
		if(guiButts[i][0]!=NULL)
		{
			fprintf(fp,"\tframe.add(%sButton);\n",guiButts[i][0]);

		}
	}
	//Write basic GUI values
	fprintf(fp,"\nframe.setSize(600,600);\n");
	fprintf(fp,"frame.setVisible(true);\n");
	fprintf(fp,"frame.setResizable(false);\n");
	fprintf(fp,"frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );\n");
	fprintf(fp,"editArea.setText(\"\");\n");
	fprintf(fp,"frame.add(editorWindow);\n");
	fprintf(fp,"}\n");

	//Set actions
	fprintf(fp,"public void actionPerformed(ActionEvent E) {\n");

	for(int i=0;i<100;i++)
	{
		if(guiButts[i][0]!=NULL)
		{
			fprintf(fp,"\tif (E.getActionCommand() ==\"%s\") {\n",guiButts[i][0]);
			//fprintf(fp,"\t\teditArea.append(\"%s button pressed\"+\"\\n\");\n",guiButts[i][0]);
			for(int j=0;j<100;j++)
			{
				if(guiFields[j][0]!=NULL)
				{
					fprintf(fp,"\tgetDC%s ();\n",guiFields[j][0]);
				}

			}
			fprintf(fp,"\teditArea.append(\" \\n\");\n");
			fprintf(fp,"\t\t}\n");

		}
	}
	fprintf(fp,"}\n");
	for(int i=0;i<100;i++)
	{
		if(guiFields[i][0]!=NULL)
		{
			if((strcmp(ftypes[i][0],"int")==0))
			{
				fprintf(fp,"public %s getDC%s () {\n",ftypes[i][0],guiFields[i][0]);
				fprintf(fp,"\t\tString %sTest = %stField.getText();\n",guiFields[i][0],guiFields[i][0]);
				fprintf(fp,"\t\tint valid=1;\n");
				fprintf(fp,"\t\ttry {\n");
				fprintf(fp,"\t\t\tvalid=Integer.parseInt(%sTest);\n",guiFields[i][0]);
				fprintf(fp,"\t\t\t} catch (NumberFormatException e) {\n");
				fprintf(fp,"\t\t\tvalid=-999;\n");
				fprintf(fp,"\t\t\t\teditArea.append(\"%s: Invalid Type\\n\");\n",guiFields[i][0]);
				fprintf(fp,"\t\t\t}\n");
				fprintf(fp,"\t\tif(valid!=-999)\n");
				fprintf(fp,"\t\t\t\teditArea.append(\"%s: \"+valid+\"\\n\");\n",guiFields[i][0]);
				fprintf(fp,"\t\treturn valid;\n");
				fprintf(fp,"\t}\n");
			}
			if((strcmp(ftypes[i][0],"double")==0))
			{
				fprintf(fp,"public %s getDC%s () {\n",ftypes[i][0],guiFields[i][0]);
				fprintf(fp,"\t\tString %sTest = %stField.getText();\n",guiFields[i][0],guiFields[i][0]);
				fprintf(fp,"\t\tdouble valid=1;\n");
				fprintf(fp,"\t\ttry {\n");
				fprintf(fp,"\t\t\tvalid=Double.parseDouble(%sTest);\n",guiFields[i][0]);
				fprintf(fp,"\t\t\t} catch (NumberFormatException e) {\n");
				fprintf(fp,"\t\t\tvalid=-999;\n");
				fprintf(fp,"\t\t\t\teditArea.append(\"%s: Invalid Type\\n\");\n",guiFields[i][0]);
				fprintf(fp,"\t\t\t}\n");
				fprintf(fp,"\t\tif(valid!=-999)\n");
				fprintf(fp,"\t\t\t\teditArea.append(\"%s: \"+valid+\"\\n\");\n",guiFields[i][0]);
				fprintf(fp,"\t\treturn valid;\n");
				fprintf(fp,"\t}\n");
			}
			if((strcmp(ftypes[i][0],"String")==0))
			{
				fprintf(fp,"public %s getDC%s () {\n",ftypes[i][0],guiFields[i][0]);
				fprintf(fp,"\t\tString %sString = %stField.getText();\n",guiFields[i][0],guiFields[i][0]);
				fprintf(fp,"\tif(%stField.getText().equals(\"\"))\n",guiFields[i][0]);
				fprintf(fp,"\t\t\t\t{editArea.append(\"%s: Empty String\\n\");}\n",guiFields[i][0]);
				fprintf(fp,"\telse\n{\n");
				fprintf(fp,"\t\t\teditArea.append(\"%s: \"+%sString+\"\\n\");\n}\n",guiFields[i][0],guiFields[i][0]);
				fprintf(fp,"\t\treturn %sString;\n",guiFields[i][0]);
				fprintf(fp,"\t}\n");
			}

		}
	}
	fprintf(fp,"\tpublic void appendToStatusArea (String message){\n\n\t}\n");
	//Run itself
	fprintf(fp,"\tpublic  static void main ( String[] args ){");
	fprintf(fp,"\t\n\t\t%s ex = new %s();\n\t}\n",title,title);
	fprintf(fp,"}\n");
	fclose(fp);
}

//Compile after the file is written
JNIEXPORT void JNICALL Java_Dialogc_DialogcCompile(JNIEnv *env , jobject job, jstring filePath, jstring dir)
{
	char * title=PM_getValue(params,"title").str_val;
	const char *wDir = (*env)->GetStringUTFChars(env,dir,NULL);
	char *path=(char *)malloc(sizeof(char)*100);
	// char *str;
	strcpy(path,wDir);
	strcat(path,"/");
	for(int i=0;i<strlen(title);i++)
	{
		if(title[i]==' ')
		title[i]='_';
	}
	strcat(path,title);
	//	strcat(path,"FieldEdit");
	strcat(path,".java");
	char command[50];
	strcpy( command, "javac " );
	strcat( command, title );
	strcat(command,".java");
	system(command);
}

//Compile and run after the file is written
JNIEXPORT void JNICALL Java_Dialogc_DialogcCRun(JNIEnv *env, jobject obj, jstring filePath, jstring dir)
{
	char * title=PM_getValue(params,"title").str_val;
	const char *wDir = (*env)->GetStringUTFChars(env,dir,NULL);
	char *path=(char *)malloc(sizeof(char)*100);
	// char *str;
	strcpy(path,wDir);
	strcat(path,"/");
	for(int i=0;i<strlen(title);i++)
	{
		if(title[i]==' ')
		title[i]='_';
	}
	strcat(path,title);
	strcat(path,".java");


	char command[50];
	strcpy( command, "javac " );
	strcat( command, title );
	strcat(command,".java");
	system(command);

	strcpy( command, "java " );
	strcat( command, title);
	system(command);
}
