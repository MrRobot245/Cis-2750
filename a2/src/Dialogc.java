/*
* ------------------------------------------------------------------
*  Dialogc.java - A gui that takes a text input and parses it based on A1
*
*  CIS*2750 - Software Systems Development and Integration
*  School of Computer Science
*  University of Guelph
*  Author: Nathan Reymer
* ------------------------------------------------------------------
*/

import java.awt.*;
import java.io.*;
import java.nio.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.KeyEvent;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.GraphicsEnvironment;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Dialogc extends JFrame implements ActionListener
{
    //Define all the native methods
    static {System.loadLibrary("Dialog"); }
    native void DialogcCreate(int size);
    native void DialogcParse(String filePath);
    native void DialogcManage();
    native void DialogcPeek();
    native void DialogcWrite(String filePath, String dir);
    native void DialogcCompile(String filePath, String dir);
    native void DialogcCRun(String filePath, String dir);


    public Dialogc()
    {

        guiUI();
    }
    //Keep track of the current filepath and work directory
    private String curFile="NULL";
    private String curFilePath="NULL";
    private String curWDir="NULL";
    JTextArea editArea = new JTextArea(6, 20);
    private void guiUI()
    {
        //All Mah Icons
        String[] iconFiles = { "new.gif", "open.gif", "save.gif", "saveAS.gif"};
        String[] buttonLabels = { "New", "Open", "Save", "SaveAs"};
        ImageIcon[] icons = new ImageIcon[iconFiles.length];
        JButton[] buttons = new JButton[buttonLabels.length];

        //Define all GUI elements

        JMenuBar menubar = new JMenuBar();
        JMenu file = new JMenu("File");
        file.setMnemonic(KeyEvent.VK_F);
        JMenu compile = new JMenu("Compile");
        JMenu config = new JMenu("Config");
        JMenu help = new JMenu("Help");
        JMenuItem newF = new JMenuItem("New");
        file.setMnemonic(KeyEvent.VK_N);
        JMenuItem open = new JMenuItem("Open");
        file.setMnemonic(KeyEvent.VK_O);
        JMenuItem save = new JMenuItem("Save");
        file.setMnemonic(KeyEvent.VK_S);
        JMenuItem saveAs = new JMenuItem("Save As");
        JMenuItem quit = new JMenuItem("Quit");


        JMenuItem compileM = new JMenuItem("Compile");
        JMenuItem compileRun = new JMenuItem("Compile and Run");
        JMenuItem javaComp = new JMenuItem("Java Compiler");
        JMenuItem cOpt = new JMenuItem("Compile options");
        JMenuItem jRun = new JMenuItem("Java Run-time");
        JMenuItem rOpt = new JMenuItem("Run-time options");
        JMenuItem wDir = new JMenuItem("Working Directory");
        JMenuItem helpM = new JMenuItem("Help");
        JMenuItem about = new JMenuItem("About");


        JFrame frame= new JFrame("Editor");


        JToolBar toolbar = new JToolBar();
        ImageIcon nIcon = new ImageIcon("src/images/new.png","New");
        JButton newButton = new JButton(nIcon);
        ImageIcon oIcon = new ImageIcon("src/images/open.png");
        JButton openButton = new JButton(oIcon);
        ImageIcon sIcon = new ImageIcon("src/images/save.png");
        JButton saveButton = new JButton(sIcon);
        ImageIcon sAIcon = new ImageIcon("src/images/saveas.png");
        JButton saveAsButton = new JButton(sAIcon);
        ImageIcon cIcon = new ImageIcon("src/images/compile.png");
        JButton cButton = new JButton(cIcon);




        //Add the menu items and toolbar for the editor GUI
        file.add(newF);
        file.add(open);
        file.add(save);
        file.add(saveAs);
        file.add(quit);
        newF.addActionListener(this);
        open.addActionListener(this);
        save.addActionListener(this);
        saveAs.addActionListener(this);
        quit.addActionListener(this);

        compile.add(compileM);
        compile.add(compileRun);
        compileM.addActionListener(this);
        compileRun.addActionListener(this);

        config.add(javaComp);
        config.add(cOpt);
        config.add(jRun);
        config.add(rOpt);
        config.add(wDir);
        javaComp.addActionListener(this);
        cOpt.addActionListener(this);
        jRun.addActionListener(this);
        rOpt.addActionListener(this);
        wDir.addActionListener(this);

        help.add(helpM);
        help.add(about);
        helpM.addActionListener(this);
        about.addActionListener(this);

        menubar.add(file);
        menubar.add(compile);
        menubar.add(config);
        menubar.add(help);

        //Initalize the text area
        editArea.setText("Enter Text or Open a File");
        curWDir=System.getProperty("user.dir");
        JScrollPane scrollingArea = new JScrollPane(editArea);
        JPanel editorWindow = new JPanel();
        editorWindow.setLayout(new BorderLayout());
        editorWindow.add(scrollingArea, BorderLayout.CENTER);
        frame.add(editorWindow);


        toolbar.setFloatable(false);
        toolbar.add(newButton);
        toolbar.add(openButton);
        toolbar.add(saveButton);
        toolbar.add(saveAsButton);
        toolbar.add(cButton);
        newButton.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                //Check for unsaved changes
                editArea.setText("Enter Text or Open a File");
            }
        });
        //Open Button Icon action
        openButton.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                JFileChooser choose = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter("Configuration", "config");
                try {
                    File f = new File(new File(".").getCanonicalPath());
                    choose.setCurrentDirectory(f);
                    choose.setCurrentDirectory(null);
                    choose.setFileFilter(filter);
                    File curDir = choose.getCurrentDirectory();
                    choose.setDialogTitle("Specify a filename");
                    int returnVal = choose.showOpenDialog(null);

                    if (returnVal == JFileChooser.APPROVE_OPTION)
                    {
                        curFile=choose.getSelectedFile().getName();
                        curFilePath=choose.getSelectedFile().getAbsolutePath();
                        File fileToopen = choose.getSelectedFile();
                        BufferedReader br = new BufferedReader(new FileReader(fileToopen));
                        String line;
                        editArea.setText("");
                        while ((line = br.readLine()) != null)
                        {
                            editArea.append(line+"\n");
                        }
                        br.close();
                    }
                }
                catch (IOException E)
                {
                }

            }
        });

        //SaveButton Icon action
        saveButton.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                if(curFile.equals("NULL"))
                {
                    Dialogc.infoBox("You havent opened a file yet!","Warning");
                }
                else
                {
                    try{
                        FileWriter fileOut = new FileWriter(curFilePath, false);
                        editArea.write(fileOut);
                    }
                    catch (IOException E)
                    {
                        Dialogc.infoBox("Error writing file!","Error");
                    }
                }
            }
        });
        //SaveAS Button Icon action
        saveAsButton.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                JFileChooser choose = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter("Configuration", "config");
                try {
                    File f = new File(new File(".").getCanonicalPath());
                    choose.setCurrentDirectory(f);
                    choose.setCurrentDirectory(null);
                    choose.setFileFilter(filter);
                    File curDir = choose.getCurrentDirectory();
                    choose.setDialogTitle("Specify a filename");
                    choose.setSelectedFile(new File("myGui.config"));
                    choose.showSaveDialog(null);
                    FileWriter fileOut = new FileWriter(choose.getSelectedFile().getAbsoluteFile(), false);
                    System.out.println("Writing File");
                    editArea.write(fileOut);
                }
                catch (IOException E)
                {
                    Dialogc.infoBox("Error writing file!","Error");
                }
            }
        });
        //Compile and Run icon action
        cButton.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                if(curFilePath.equals("NULL"))
                {
                    Dialogc.infoBox("You havent opened a file yet!","Warning");
                }
                else
                {
                    DialogcCreate(60);
                    DialogcParse(curFilePath);
                    DialogcManage();
                    DialogcParse(curFilePath);
                    DialogcPeek();
                    DialogcWrite(curFilePath,curWDir);
                    DialogcCompile(curFilePath, curWDir);
                    DialogcCRun(curFilePath,curWDir);
                }
            }
        });



        //End Menu and Toolbars
        //Window Settings
        frame.setJMenuBar(menubar);
        frame.add(toolbar,BorderLayout.NORTH);



        frame.setSize(800,800);
        frame.setVisible( true );
        frame.setResizable(false);
        frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

        //Get editable text window both x and Y scroll


    }
    //Actions for menu Items, mostly repeated

    public void actionPerformed(ActionEvent E) {
        if (E.getActionCommand() == "Quit") {
            System.exit(0);
        }
        if(E.getActionCommand()=="Open")
        {
            JFileChooser choose = new JFileChooser();
            FileNameExtensionFilter filter = new FileNameExtensionFilter("Configuration", "config");
            try {
                File f = new File(new File(".").getCanonicalPath());
                choose.setCurrentDirectory(f);
                choose.setCurrentDirectory(null);
                choose.setFileFilter(filter);
                File curDir = choose.getCurrentDirectory();
                choose.setDialogTitle("Specify a filename");
                int returnVal = choose.showOpenDialog(null);

                if (returnVal == JFileChooser.APPROVE_OPTION)
                {
                    curFile=choose.getSelectedFile().getName();
                    curFilePath=choose.getSelectedFile().getAbsolutePath();
                    File fileToopen = choose.getSelectedFile();
                    BufferedReader br = new BufferedReader(new FileReader(fileToopen));
                    String line;
                    editArea.setText("");
                    while ((line = br.readLine()) != null)
                    {
                        editArea.append(line+"\n");
                    }
                    br.close();
                }
            } catch (IOException O) {
                // Do something here
            }

        }
        if(E.getActionCommand()=="Save")
        {
            if(curFile.equals("NULL"))
            {
                Dialogc.infoBox("You havent opened a file yet!","Warning");
            }
            else
            {
                try{
                    FileWriter fileOut = new FileWriter(curFilePath, false);
                    editArea.write(fileOut);
                }
                catch (IOException S)
                {
                    Dialogc.infoBox("Error writing file!","Error");
                }

            }
        }
        if(E.getActionCommand()=="Save As")
        {
            JFileChooser choose = new JFileChooser();
            FileNameExtensionFilter filter = new FileNameExtensionFilter("Configuration", "config");
            try {
                File f = new File(new File(".").getCanonicalPath());
                choose.setCurrentDirectory(f);
                choose.setCurrentDirectory(null);
                choose.setFileFilter(filter);
                File curDir = choose.getCurrentDirectory();
                choose.setDialogTitle("Specify a filename");
                int returnVal = choose.showOpenDialog(null);

                if (returnVal == JFileChooser.APPROVE_OPTION)
                {
                    curFile=choose.getSelectedFile().getName();
                    curFilePath=choose.getSelectedFile().getAbsolutePath();
                    File fileToopen = choose.getSelectedFile();
                    BufferedReader br = new BufferedReader(new FileReader(fileToopen));
                    String line;
                    editArea.setText("");
                    while ((line = br.readLine()) != null)
                    {
                        editArea.append(line+"\n");
                    }
                    br.close();
                }
            } catch (IOException SA) {
                // Do something here
            }
        }
        if(E.getActionCommand()== "Working Directory")
        {
            //CHANGE curWDir
            JFileChooser choose = new JFileChooser();
            File curDir = choose.getCurrentDirectory();
            choose.setDialogTitle("Specify a Directory");
            choose.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
            int returnVal = choose.showOpenDialog(null);
            if(returnVal==choose.APPROVE_OPTION)
            {
                curWDir=choose.getSelectedFile().getAbsolutePath();
            }
            else
            {
            }
        }
        if(E.getActionCommand()=="Compile")
        {
            if(curFilePath.equals("NULL"))
            {
                Dialogc.infoBox("You havent opened a file yet!","Warning");
            }
            else
            {
                DialogcCreate(60);
                DialogcParse(curFilePath);
                DialogcManage();
                DialogcParse(curFilePath);
                DialogcPeek();
                DialogcWrite(curFilePath,curWDir);
                DialogcCompile(curFilePath, curWDir);
            }
        }
        if(E.getActionCommand()=="Compile and Run")
        {
            if(curFilePath.equals("NULL"))
            {
                Dialogc.infoBox("You havent opened a file yet!","Warning");
            }
            else
            {
                DialogcCreate(60);
                DialogcParse(curFilePath);
                DialogcManage();
                DialogcParse(curFilePath);
                DialogcPeek();
                DialogcWrite(curFilePath,curWDir);
                DialogcCompile(curFilePath, curWDir);
                DialogcCRun(curFilePath,curWDir);
            }
        }
        if(E.getActionCommand()=="Compile options")
        {

        //Probably have to put LEXX/YACC here

        }
        if(E.getActionCommand()=="Java Compiler")
        {
        }
        if(E.getActionCommand()=="Java Run-time")
        {
        }
        if(E.getActionCommand()=="Java Run-time")
        {
        }
        if (E.getActionCommand() == "Help")
        {
            Dialogc.infoBox("0797359 \nNathan Reymer","Help");
        }
        if (E.getActionCommand() == "About")
        {
            Dialogc.infoBox("0797359 \nNathan Reymer","About");
        }

    }
    //Custom message window
    public static void infoBox(String infoMessage, String titleBar)
    {
        JOptionPane.showMessageDialog(null, infoMessage, titleBar, JOptionPane.INFORMATION_MESSAGE);
    }
    //Call itself
    public  static void main ( String[] args )
    {

        Dialogc ex = new Dialogc();

    }

}
