import java.awt.*;
import java.io.*;
import java.nio.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
public class Video_Way_Customer_Records extends JFrame implements ActionListener
{
public Video_Way_Customer_Records()
{
	guiUI();
}
	JTextArea editArea = new JTextArea(6, 20);
	JLabel MemberNumberLbl= new JLabel("MemberNumber");
	JTextField MemberNumbertField= new JTextField();
	JLabel LastNameLbl= new JLabel("LastName");
	JTextField LastNametField= new JTextField();
	JLabel FirstNameLbl= new JLabel("FirstName");
	JTextField FirstNametField= new JTextField();
	JLabel AddressLbl= new JLabel("Address");
	JTextField AddresstField= new JTextField();
	JLabel TotalRentalsLbl= new JLabel("TotalRentals");
	JTextField TotalRentalstField= new JTextField();
	JLabel Account_balanceLbl= new JLabel("Account_balance");
	JTextField Account_balancetField= new JTextField();
private void guiUI()
{
	MemberNumberLbl.setBounds(30, 40, 150, 80);
	MemberNumbertField.setBounds(180, 75, 300, 20);
	LastNameLbl.setBounds(30, 70, 150, 80);
	LastNametField.setBounds(180, 105, 300, 20);
	FirstNameLbl.setBounds(30, 100, 150, 80);
	FirstNametField.setBounds(180, 135, 300, 20);
	AddressLbl.setBounds(30, 130, 150, 80);
	AddresstField.setBounds(180, 165, 300, 20);
	TotalRentalsLbl.setBounds(30, 160, 150, 80);
	TotalRentalstField.setBounds(180, 195, 300, 20);
	Account_balanceLbl.setBounds(30, 190, 150, 80);
	Account_balancetField.setBounds(180, 225, 300, 20);
	JButton AddButton= new JButton("Add");
	AddButton.setBounds(60,275,90,40);
	AddButton.addActionListener(this);
	JButton UpdateButton= new JButton("Update");
	UpdateButton.setBounds(160,275,90,40);
	UpdateButton.addActionListener(this);
	JButton DeleteButton= new JButton("Delete");
	DeleteButton.setBounds(260,275,90,40);
	DeleteButton.addActionListener(this);
	JButton QueryButton= new JButton("Query");
	QueryButton.setBounds(360,275,90,40);
	QueryButton.addActionListener(this);
	JButton PrintButton= new JButton("Print");
	PrintButton.setBounds(460,275,90,40);
	PrintButton.addActionListener(this);
	JFrame frame= new JFrame("Video Way Customer Records");

JScrollPane scrollingArea = new JScrollPane(editArea);
JPanel editorWindow = new JPanel();
editorWindow.setBounds(0,300,600,250);
editorWindow.setLayout(new BorderLayout());
editorWindow.add(scrollingArea, BorderLayout.SOUTH);
frame.setLayout(null);

	frame.add(MemberNumberLbl);
	frame.add(MemberNumbertField);
	frame.add(LastNameLbl);
	frame.add(LastNametField);
	frame.add(FirstNameLbl);
	frame.add(FirstNametField);
	frame.add(AddressLbl);
	frame.add(AddresstField);
	frame.add(TotalRentalsLbl);
	frame.add(TotalRentalstField);
	frame.add(Account_balanceLbl);
	frame.add(Account_balancetField);
	frame.add(AddButton);
	frame.add(UpdateButton);
	frame.add(DeleteButton);
	frame.add(QueryButton);
	frame.add(PrintButton);

frame.setSize(600,600);
frame.setVisible(true);
frame.setResizable(false);
frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
editArea.setText("");
frame.add(editorWindow);
}
public void actionPerformed(ActionEvent E) {
	if (E.getActionCommand() =="Add") {
	getDCMemberNumber ();
	getDCLastName ();
	getDCFirstName ();
	getDCAddress ();
	getDCTotalRentals ();
	getDCAccount_balance ();
	editArea.append(" \n");
		}
	if (E.getActionCommand() =="Update") {
	getDCMemberNumber ();
	getDCLastName ();
	getDCFirstName ();
	getDCAddress ();
	getDCTotalRentals ();
	getDCAccount_balance ();
	editArea.append(" \n");
		}
	if (E.getActionCommand() =="Delete") {
	getDCMemberNumber ();
	getDCLastName ();
	getDCFirstName ();
	getDCAddress ();
	getDCTotalRentals ();
	getDCAccount_balance ();
	editArea.append(" \n");
		}
	if (E.getActionCommand() =="Query") {
	getDCMemberNumber ();
	getDCLastName ();
	getDCFirstName ();
	getDCAddress ();
	getDCTotalRentals ();
	getDCAccount_balance ();
	editArea.append(" \n");
		}
	if (E.getActionCommand() =="Print") {
	getDCMemberNumber ();
	getDCLastName ();
	getDCFirstName ();
	getDCAddress ();
	getDCTotalRentals ();
	getDCAccount_balance ();
	editArea.append(" \n");
		}
}
public int getDCMemberNumber () {
		String MemberNumberTest = MemberNumbertField.getText();
		int valid=1;
		try {
			valid=Integer.parseInt(MemberNumberTest);
			} catch (NumberFormatException e) {
			valid=-999;
				editArea.append("MemberNumber: Invalid Type\n");
			}
		if(valid!=-999)
				editArea.append("MemberNumber: "+valid+"\n");
		return valid;
	}
public String getDCLastName () {
		String LastNameString = LastNametField.getText();
	if(LastNametField.getText().equals(""))
				{editArea.append("LastName: Empty String\n");}
	else
{
			editArea.append("LastName: "+LastNameString+"\n");
}
		return LastNameString;
	}
public String getDCFirstName () {
		String FirstNameString = FirstNametField.getText();
	if(FirstNametField.getText().equals(""))
				{editArea.append("FirstName: Empty String\n");}
	else
{
			editArea.append("FirstName: "+FirstNameString+"\n");
}
		return FirstNameString;
	}
public String getDCAddress () {
		String AddressString = AddresstField.getText();
	if(AddresstField.getText().equals(""))
				{editArea.append("Address: Empty String\n");}
	else
{
			editArea.append("Address: "+AddressString+"\n");
}
		return AddressString;
	}
public int getDCTotalRentals () {
		String TotalRentalsTest = TotalRentalstField.getText();
		int valid=1;
		try {
			valid=Integer.parseInt(TotalRentalsTest);
			} catch (NumberFormatException e) {
			valid=-999;
				editArea.append("TotalRentals: Invalid Type\n");
			}
		if(valid!=-999)
				editArea.append("TotalRentals: "+valid+"\n");
		return valid;
	}
public double getDCAccount_balance () {
		String Account_balanceTest = Account_balancetField.getText();
		double valid=1;
		try {
			valid=Double.parseDouble(Account_balanceTest);
			} catch (NumberFormatException e) {
			valid=-999;
				editArea.append("Account_balance: Invalid Type\n");
			}
		if(valid!=-999)
				editArea.append("Account_balance: "+valid+"\n");
		return valid;
	}
	public void appendToStatusArea (String message){

	}
	public  static void main ( String[] args ){	
		Video_Way_Customer_Records ex = new Video_Way_Customer_Records();
	}
}
