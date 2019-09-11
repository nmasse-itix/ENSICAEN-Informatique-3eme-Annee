// DomParserDemo.java
// Modifie un arbre DOM

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.FactoryConfigurationError;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

import java.io.File;
import java.io.IOException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.DOMException;
import org.w3c.dom.NamedNodeMap;

import java.util.*;

public class DOMParserDemo {
  public void performDemo(String uri)  {
    DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
    try {
      DocumentBuilder builder = factory.newDocumentBuilder();
      Document doc = builder.parse(new File(uri));
      
      doc = transform(doc);
      printNode(doc);
    } catch (Throwable t) {
      t.printStackTrace ();
      System.exit (1);
    }

    System.exit (0);
  }

  public Document transform(Document doc) {
    Element root = doc.getDocumentElement();
    NodeList rnl = root.getChildNodes();
    
    // 
    Node ge = null;
    Node me = null;
    Node de = null;

    int s = rnl.getLength();
    for (int i = 0; i < s; i++) {
      Node n = rnl.item(i);
      if (n instanceof Element) {
        String name = n.getNodeName();
        if ("groupes".equals(name)) {
          ge = n;
        } else if ("musiciens".equals(name)) {
          me = n;
        } else if ("disques".equals(name)) {
          de = n;
        }
      }
    }
    
    Map<String, Node> groups = new HashMap<String, Node>();
    Map<String, Node> groups2 = new HashMap<String, Node>();

    NodeList groupList = ge.getChildNodes();
    s = groupList.getLength();
    for (int i = 0; i < s; i++) {
      Node element = groupList.item(i);
      if (element instanceof Element) {
        NamedNodeMap att = element.getAttributes();
        Node tmp = me.cloneNode(false);
        element.appendChild(tmp);
        groups.put(att.getNamedItem("id").getNodeValue(), tmp);
        tmp = de.cloneNode(false);
        element.appendChild(tmp);
        groups2.put(att.getNamedItem("id").getNodeValue(), tmp);
      }
    }
    
    NodeList musicienList = me.getChildNodes();
    s = musicienList.getLength();
    for (int i = 0; i < s; i++) {
      Node element = musicienList.item(i);
      if (element instanceof Element) {
        NamedNodeMap att = element.getAttributes();
        String attVal = att.getNamedItem("groupe").getNodeValue();
        ((Node) groups.get(attVal)).appendChild(element);
      }
    }

    NodeList disqueList = de.getChildNodes();
    s = disqueList.getLength();
    for (int i = 0; i < s; i++) {
      Node element = disqueList.item(i);
      if (element instanceof Element) {
        NamedNodeMap att = element.getAttributes();
        String attVal = att.getNamedItem("groupe").getNodeValue();
        ((Node) groups2.get(attVal)).appendChild(element);
      }
    }

    root.removeChild(de);
    root.removeChild(me);

    return doc;
  }

  public void p(Object o) {
    System.out.println(o);
  }

  public void printNode(Node node) {
    switch (node.getNodeType()) {
    case Node.DOCUMENT_NODE:
     Document doc = (Document) node;
     System.out.println("<?xml version=\"1.0\"?>");
     printNode(doc.getDocumentElement());
     break;
    case Node.ELEMENT_NODE:
     System.out.print("<"+node.getNodeName());
     NamedNodeMap attributs = node.getAttributes();
     for (int i=0; i<attributs.getLength(); i++) {
        System.out.print(" " + 
        attributs.item(i).getNodeName() + "=\"" + 
        attributs.item(i).getNodeValue() + "\"");
     }
     System.out.print(">");
     NodeList children = node.getChildNodes();
     if (children != null) {
        for (int i=0; i<children.getLength(); i++) {
          printNode(children.item(i));
        }
     }
     System.out.print("</"+node.getNodeName()+">");
     break;

    case Node.TEXT_NODE:
     System.out.print(node.getNodeValue());
     break;
    }
  }

  public static void main(String[] argv) {
    if (argv.length != 1) {
      System.err.println ("Usage: cmd filename > sortie");
      System.exit (1);
    }
   
    String uri = argv[0];
    //System.out.println("En train de traiter fichier "+uri);
    DOMParserDemo parserDemo = new DOMParserDemo();
    parserDemo.performDemo(uri);
  }
}

