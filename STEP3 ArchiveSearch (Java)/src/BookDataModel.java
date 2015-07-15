import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;

import javax.swing.JTextArea;

public class BookDataModel {
	BookDataModel(){
    }
	private	HashMap<Integer,Integer> tempdata=new HashMap<Integer,Integer>();
	public int bookEnter(String title,String writer,String publisher,String ISBN,JTextArea a1){
		String[] writeData=new String[4];
		BufferedWriter buffWriter = null;
		try{
			buffWriter = new BufferedWriter(new FileWriter("bookList.txt",true));
			writeData[0] = title;
            buffWriter.write(writeData[0]);
            buffWriter.newLine();
            writeData[1] = writer;
            buffWriter.write(writeData[1]);
            buffWriter.newLine();
            writeData[2] = publisher;
            buffWriter.write(writeData[2]);
            buffWriter.newLine();
            writeData[3] = ISBN;
            buffWriter.write(writeData[3]);
            buffWriter.newLine();
        }
        catch(IOException e){
            System.out.println("Write Error");
            return 0;
        }finally{
            try{
                buffWriter.flush();
                buffWriter.close();
                a1.setText("SUCCESS : DATA REGISTED"+"\n");
                for(int i=0;i<4;i++){
                	a1.append(writeData[i]+"\n");
                }
            }
            catch(Exception e){
                System.out.println("Close Error");
                return 0;
            }
        }
    	return 1;
    }
	public void bookSearch(String title,String writer,String publisher,String ISBN,JTextArea a1){
		String[] str = new String[4];
		int key=0;	//検索条件が複数ある時のため
		str[0]=title;str[1]=writer;str[2]=publisher;str[3]=ISBN;
		for(int i=0;i<4;i++){
            System.out.println(str[i]);
			if(!str[i].equals("")){
				searcher(str[i],a1);
				key++;	//最適ヒット回数
			}
		}
		show(key,a1);
		tempdata.clear();
		}
	
	public void showall(JTextArea a1){
		a1.setText("SHOW ALL BOOK-DATA"+"\n\n");
		String readData="";
		BufferedReader buffReader = null;
		String[] check = new String[4];
		try{
			buffReader = new BufferedReader(new FileReader("bookList.txt"));
			readData = buffReader.readLine();
			while(readData != null){
				for(int j=0;j<4;j++){
					check[j]=readData;
					readData = buffReader.readLine();
					a1.append(check[j]+"\n");
					}
				a1.append("\n");
			}
		}
		catch(IOException e){
            System.out.println("Read Error");
        }
		finally{
            try{
                buffReader.close();
            }
            catch(Exception e){
                System.out.println("Close Error");
            }
		}
	}
	
	public void searcher(String str,JTextArea a1){
		System.out.println("search");
		int temp;
		String readData="";
		String[] check = new String[4];
		BufferedReader buffReader = null;
		int i=0;
		try{
			buffReader = new BufferedReader(new FileReader("bookList.txt"));
			readData = buffReader.readLine();
			while(readData != null){
			for(int j=0;j<4;j++){
				check[j]=readData;
				readData = buffReader.readLine();
				}
	    	System.out.printf(check[0]+check[1]+check[2]+check[3]+"\n");
	    	for(int k=0;k<4;k++){
	    		if(check[k].contains(str)){
	    			if(tempdata.containsKey(i)){
		    			System.out.println("c1");
	    				temp=tempdata.get(i)+1;
		    			System.out.println("c2");
	    				tempdata.put(i,temp);
		    			System.out.println(i);System.out.println(tempdata.get(i));
	    			}else{
	    			tempdata.put(i,0);
	    			System.out.println(i);System.out.println(tempdata.get(i));
	    			}
	    			}
	    		}
	    	i++;
			}
			}
		catch(IOException e){
            System.out.println("Read Error");
            }
		finally{
            try{
                buffReader.close();
            }
            catch(Exception e){
                System.out.println("Close Error");
            }
        }
	}
	
	public void show(int key,JTextArea a1){
		System.out.printf("show\n");
		String readData="";
		String[] check = new String[4];
		BufferedReader buffReader = null;
		int i=0;
		try{
			buffReader = new BufferedReader(new FileReader("bookList.txt"));
			readData = buffReader.readLine();
			while(readData != null){
				for(int j=0;j<4;j++){
					check[j]=readData;
					readData = buffReader.readLine();
				}
		    	System.out.printf(check[0]+check[1]+check[2]+check[3]+"\n");
		    	if(tempdata.containsKey(i)){
		    		int l=tempdata.get(i);
		    		System.out.println(i);System.out.println(l);
		    		if((key-1)==tempdata.get(i)){
		    		System.out.printf("hit\n");
		    			for(int j=0;j<4;j++){
		    				a1.append(check[j]+"\n");
		    			}
		    			a1.append("\n");
		    		}
				}
				i++;
			}
		}
		catch(IOException e){
            System.out.println("Read Error");
        }
		finally{
            try{
                buffReader.close();
            }
            catch(Exception e){
                System.out.println("Close Error");
            }
        }
	}
}