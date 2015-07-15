import javax.swing.table.DefaultTableModel;

class SASKaiCtrl {
    private SASKaiModel mdl;

    SASKaiCtrl(){
        mdl = new SASKaiModel();
    }
    public void expressResult(String str,DefaultTableModel tm){
    	if( str!= null && str.length() != 0 ){
    		str="WHERE "+str;
    	}
    	mdl.expressResult(str,tm);
    }
    
    public void del(String str,DefaultTableModel tm){
    	if( str!= null && str.length() != 0 ){
    		str="WHERE "+str;
    	}
    	mdl.del(str,tm);
    }
    public void modi(String str,String[] data,DefaultTableModel tm){
    	String temp="";
    	int i,j=0;
    	for(i=0;i<4;i++){
    		if( data[i]!= null && data[i].length() != 0 ){
    			if(j>0){
    				temp+=", ";
    			}
    			switch (i){
    			case (0):temp+="sno='"+data[i]+"'";break;
    			case (1):temp+="sname='"+data[i]+"'";break;
    			case (2):temp+="address='"+data[i]+"'";break;
    			case (3):temp+="age="+data[i];break;
    			}
    			j++;
    			}
    		}
    	if( str!= null && str.length() != 0 ){
    		temp+="WHERE "+str;
    	}
    	mdl.modi(temp,tm);
    }
    public void regi(String[] data,DefaultTableModel tm){
    	String temp="(";
    	int i,j=0;
    	for(i=0;i<4;i++){
    		if( data[i]!= null && data[i].length() != 0 ){
    			j++;
    	}
    	}
    	if(j>0){
    	for(i=0;i<4;i++){
    			switch (i){
    			case (0):temp+="'"+data[i]+"'";break;
    			case (1):temp+=",'"+data[i]+"'";break;
    			case (2):temp+=",'"+data[i]+"'";break;
    			case (3):temp+=","+data[i]+")";break;
    			}
    		}
    	mdl.regi(temp,tm);
    	}
    }
    public void allDel(DefaultTableModel tm){
    	mdl.allDel(tm);
    }
}