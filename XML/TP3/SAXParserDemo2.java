// SAXParserDemo.java
//
// Parse avec l'Api SAX un document XML
// Transformation XML --> HTML
// +traitement des attributs
// Document pour l'ENSICAEN

import java.io.*;
import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.SAXParser;

public class SAXParserDemo2 extends DefaultHandler {
  
    private StringBuffer str;
    private boolean write;
    

    private String anneeDisque = null;
  
    public static void main (String argv[])
	throws IOException {
	if (argv.length != 1) {
	    System.err.println
		("Usage: SAXParserDemo2 fichierSource > fichierCible");
	    System.exit (1);
	}
    
	DefaultHandler handler = new SAXParserDemo2();
	SAXParserFactory factory = SAXParserFactory.newInstance();
	try {
	    SAXParser saxParser = factory.newSAXParser();
	    saxParser.parse( new File(argv[0]), handler );
	} catch (Throwable t) {
	    t.printStackTrace ();
	    System.exit (2);
	}
	System.exit (0);
    }


    public SAXParserDemo2() {
	this.str = new StringBuffer();
	this.write = false;
    }

    public void error(SAXParseException e)
	throws SAXParseException {
	throw e;
    }


    public void startDocument () throws SAXException {
	this.cat("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	this.cat("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	this.cat("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">");
	this.cat("<head>");
	this.cat("<title>Conversions XML -&gt;</title>");
	this.cat("<link rel=\"stylesheet\" type=\"text/css\" href=\"style2.css\" title=\"default style\"/>\n");
	this.cat("</head>");
	this.cat("<body>");
      
    }

    public void endDocument ()
	throws SAXException {
	this.cat("</body>");
	this.cat("</html>");
	System.out.println(this.str.toString());
    }

    public void startElement (String namespaceURI,
			      String simpleName,
			      String qualifiedName,
			      Attributes attrs)
	throws SAXException {
      
	String name = null;

	//	System.err.println("namespaceURI: " + namespaceURI + ", simpleName: " + ", qualifiedName: " + qualifiedName);

	
	if (namespaceURI.length() == 0) {
	    name = qualifiedName;
	} else {
	    name = simpleName;
	}
	

	if ("groupes".equals(name)) {
	    this.cat("<table><thead><tr><td>Photo</td><td>Musiciens</td><td>Disques</td></tr></thead><tbody>");
	}

	if ("groupe".equals(name)) {
	    String img = "img_disco/" + attrs.getValue("img");
	    String url = attrs.getValue("url");
	    this.cat("<tr><td><img src=\"");
	    this.cat(img);
	    this.cat("\" alt=\"image du groupe\" width=\"100\" height=\"100\"/></td>");
	}

	if ("musiciens".equals(name)) {
	    this.cat("<td><ul>");
	}

	if ("musicien".equals(name)) {
	    this.cat("<li>");
	    this.write = true;
	}

	if ("instruments".equals(name)) {
	    this.write = false;
	}

	if ("bio".equals(name)) {
	    this.write = false;
	}
	

	if ("disques".equals(name)) {
	     this.cat("<td><table>");
	}

	
	if ("disque".equals(name)) {
	    String img = "img_disco/" + attrs.getValue("img");
	    this.anneeDisque = attrs.getValue("annee");
	    this.cat("<tr><td><img src=\"");
	    this.cat(img);
	    this.cat("\" alt=\"image du disque\" width=\"100\" height=\"100\"/></td><td>");
	    this.cat(attrs.getValue("annee"));
	    this.cat("</td><td>");
	    this.write = true;
	}
    }

    public void endElement (String namespaceURI,
			    String simpleName,
			    String qualifiedName)
	throws SAXException {
  	String name = "";

	if (namespaceURI.length() == 0) {
	    name = qualifiedName;
	} else {
	    name = simpleName;
	}

	if ("groupes".equals(name)) {
	    this.cat("</tbody></table>");
	}

	if ("groupe".equals(name)) {
	    this.cat("</tr>");
	}
	
	if ("musiciens".equals(name)) {
	    this.cat("</ul></td>");
	}
	
	if ("musicien".equals(name)) {
	    this.cat("</li>");
	    this.write = false;
	}
	/*
	if ("instruments".equals(name)) {
	    this.cat("</td>");
	}
	*/
	if ("disques".equals(name)) {
	     this.cat("</table></td>");
	}
	
	if ("disque".equals(name)) {
	    this.cat("</td></tr>");
	    this.write = false;
	}
    }

    public void characters (char buf [], int offset, int len)
	throws SAXException {
	// String(byte[] bytes, int offset, int length)
	if (this.write) {
	    this.cat(new String(buf, offset, len));
	}
    }

  
    private void cat(String str) {
	this.str.append(str);
    }

}
