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
JNIEXPORT void JNICALL Java_Dialogc_DialogcParse(JNIEnv * env, jobject obj, jstring filePath)
{

	const char *str = (*env)->GetStringUTFChars(env,filePath,NULL);
	FILE *fp=fopen(str,"r");
	PM_parseFrom(params,fp,'#');
	fclose(fp);
}

//After parsing, look at all the fields and manage, add all values
JNIEXPORT void JNICALL Java_Dialogc_DialogcManage (JNIEnv * env, jobject job){
	char * value;
	fields = PM_getValue(params,"fields").list_val;
	buttons = PM_getValue(params,"buttons").list_val;
	while(value = PL_next(fields))
	{
		PM_manage(params,value,STRING_TYPE,1);

	}
	while(value = PL_next(buttons))
	{
		PM_manage(params,value,STRING_TYPE,1);
	}
}

//Set the values of the title and buttons into the array
JNIEXPORT void JNICALL Java_Dialogc_DialogcPeek(JNIEnv *env, jobject job)
{
	char *title;
	char * value;
	int i=0;
	fields = PM_getValue(params,"fields").list_val;
	buttons = PM_getValue(params,"buttons").list_val;
	for(int i=0;i<100;i++)
	{
		guiFields[i][0]=NULL;
		guiButts[i][0]=NULL;
	}
	while(value = PL_next(fields))
	{
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
	char *path=(char *)malloc(sizeof(char)*600);
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
	fprintf(fp,"{\npublic %s()\n{\nguiUI();\n}\n",title);
	fprintf(fp,"JTextArea editArea = new JTextArea(6, 20);\n");
	fprintf(fp,"private void guiUI()\n{\n");

	//Add Labels and text fields
	for(int i=0;i<100;i++)
	{
		if(guiFields[i][0]!=NULL)
		{
			fprintf(fp,"\tJLabel %sLbl= new JLabel(\"%s\");\n",guiFields[i][0],guiFields[i][0]);
			fprintf(fp,"\tJTextField %stField= new JTextField();\n",guiFields[i][0]);
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
	fprintf(fp,"JFrame frame= new JFrame(\"%s\");\n",title);
	fprintf(fp,"JScrollPane scrollingArea = new JScrollPane(editArea);\n");
	fprintf(fp,"JPanel editorWindow = new JPanel();\n");
	fprintf(fp,"editorWindow.setBounds(0,300,600,250);\n");
	fprintf(fp,"editorWindow.setLayout(new BorderLayout());\n");
	fprintf(fp,"editorWindow.add(scrollingArea, BorderLayout.SOUTH);\n");
	fprintf(fp,"frame.setLayout(null);\n");

	//Add labels and fields to the frame
	for(int i=0;i<100;i++)
	{
		if(guiFields[i][0]!=NULL)
		{
			fprintf(fp,"\tframe.add(%sLbl);\n",guiFields[i][0]);
			fprintf(fp,"\tframe.add(%stField);\n",guiFields[i][0]);
		}
	}
	//Add the buttons to the frams
	for(int i=0;i<100;i++)
	{
		if(guiButts[i][0]!=NULL)
		{
			fprintf(fp,"\tframe.add(%sButton);\n",guiButts[i][0]);

		}
	}
	//Write basic GUI values
	fprintf(fp,"frame.setSize(600,600);\n");
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
			fprintf(fp,"\t\teditArea.append(\"%s button pressed\"+\"\\n\");\n",guiButts[i][0]);
			fprintf(fp,"}\n");

		}
	}
	fprintf(fp,"}\n");
	for(int i=0;i<100;i++)
	{
		if(guiFields[i][0]!=NULL)
		{
			//fprintf(fp,"\tpublic String %s = getDC%s();\n",guiFields[i][0],guiFields[i][0]);

		}
		if(guiFields[i][0]!=NULL)
		{
			fprintf(fp,"\tpublic int setDC%s (String  text) {\n",guiFields[i][0]);
			fprintf(fp,"return 0;\n");
			fprintf(fp,"}\n");

		}
	}
	fprintf(fp,"public void appendToStatusArea (String message){\n\n}\n");
	//Run itself
	fprintf(fp,"public  static void main ( String[] args )\n");
	fprintf(fp,"{\n %s ex = new %s();\n}\n",title,title);
	fprintf(fp,"}\n");
	fclose(fp);

}

//Compile after the file is written
JNIEXPORT void JNICALL Java_Dialogc_DialogcCompile(JNIEnv *env , jobject job, jstring filePath, jstring dir)
{

	char * title=PM_getValue(params,"title").str_val;
	const char *wDir = (*env)->GetStringUTFChars(env,dir,NULL);
	char *path=(char *)malloc(sizeof(char)*600);
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


	char command[650];
	strcpy( command, "javac " );
	strcat( command, path );
	system(command);

	strcpy( command, "java " );
	strcat( command, title);

	//system(command);
}

//Compile and run after the file is written
JNIEXPORT void JNICALL Java_Dialogc_DialogcCRun(JNIEnv *env, jobject obj, jstring filePath, jstring dir)
{

		char * title=PM_getValue(params,"title").str_val;
		const char *wDir = (*env)->GetStringUTFChars(env,dir,NULL);
		char *path=(char *)malloc(sizeof(char)*600);
		// char *str;
		strcpy(path,wDir);
		strcat(path,"/");

		char compileC[650];
		strcpy(compileC, "java -cp " );
		strcat(compileC,path);
		strcat(compileC," ");

		for(int i=0;i<strlen(title);i++)
		{
			if(title[i]==' ')
			title[i]='_';
		}
		strcat(path,title);
		strcat(compileC,title);
		strcat(path,".java");


		char command[650];
		strcpy( command, "javac " );
		strcat( command, path );
		system(command);
		printf("Command: %s\n",command);


		printf("compileC: %s\n",compileC);
		system(compileC);
}
