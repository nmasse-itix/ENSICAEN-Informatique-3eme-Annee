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

public class SAXParserDemo extends DefaultHandler {
  
    private StringBuffer str;

    private String anneeDisque = null;
  
    public static void main (String argv[])
	throws IOException {
	if (argv.length != 1) {
	    System.err.println
		("Usage: SAXParserDemo fichierSource > fichierCible");
	    System.exit (1);
	}
    
	DefaultHandler handler = new SAXParserDemo();
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


    public SAXParserDemo() {
	this.str = new StringBuffer();
    }

    public void error(SAXParseException e)
	throws SAXParseException {
	throw e;
    }


    public void startDocument ()
	throws SAXException {
	this.cat("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	this.cat("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");
	this.cat("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n");
	this.cat("<head>\n");
	this.cat("<title>Conversions XML -&gt; XHTML</title>\n");
	this.cat("<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" title=\"default style\"/>\n");
	this.cat("</head>\n");
	this.cat("<body>\n");
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
	    this.cat("<table><thead><tr><td>Photo</td><td>Nom</td></tr></thead><tbody>\n");
	}

	if ("groupe".equals(name)) {
	    String img = "img_disco/" + attrs.getValue("img");
	    String url = attrs.getValue("url");
	    this.cat("<tr><td><img src=\"");
	    this.cat(img);
	    this.cat("\" alt=\"image du groupe\" width=\"100\" height=\"100\"/></td><td><a href=\"");
	    this.cat(url);
	    this.cat("\">");
	}

	if ("musiciens".equals(name)) {
	    this.cat("<table><thead><tr><td>Nom</td><td>Instruments</td><td>Biographie</td></tr></thead><tbody>");
	}

	if ("musicien".equals(name)) {
	    this.cat("<tr><td>");
	}

	if ("instruments".equals(name)) {
	    this.cat("</td><td>");
	}

	if ("bio".equals(name)) {
	    String att = null;
	    this.cat("<td>");

	    att = attrs.getValue("naissance");
	    if (! "-".equals(att)) {
		this.cat(att);
	    }

	    att = attrs.getValue("mort");
	    if (! "-".equals(att)) {
		this.cat(" - ");
		this.cat(att);
	    }

	    this.cat("</td>");
	}

	if ("disques".equals(name)) {
	     this.cat("<table><thead><tr><td>Photo</td><td>Titre, année</td></tr></thead><tbody>");
	}


	if ("disque".equals(name)) {
	    String img = "img_disco/" + attrs.getValue("img");
	    this.anneeDisque = attrs.getValue("annee");
	    this.cat("<tr><td><img src=\"");
	    this.cat(img);
	    this.cat("\" alt=\"image du disque\" width=\"100\" height=\"100\"/></td><td>");
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
	    this.cat("</a></td></tr>");
	}

	if ("musiciens".equals(name)) {
	    this.cat("</tbody></table>");
	}

	if ("musicien".equals(name)) {
	    this.cat("</tr>");
	}

	if ("instruments".equals(name)) {
	    this.cat("</td>");
	}

	if ("disques".equals(name)) {
	     this.cat("</tbody></table>");
	}

	if ("disque".equals(name)) {
	    this.cat(", ");
	    this.cat(this.anneeDisque);
	    this.cat("</td></tr>");
	}

    }

    public void characters (char buf [], int offset, int len)
	throws SAXException {
	// String(byte[] bytes, int offset, int length)
	this.cat(new String(buf, offset, len));
    }

  
    private void cat(String str) {
	this.str.append(str);
    }

}
