//package src;

import org.w3c.dom.*;
import org.xml.sax.SAXException;
import javax.xml.transform.*;
import javax.xml.transform.dom.*;
import javax.xml.transform.stream.*;
import javax.xml.parsers.*;
import java.io.*;
import java.text.DecimalFormat;
import java.nio.file.Paths;

class XMLGeneration {
    public static DecimalFormat df = new DecimalFormat("0.00");
    public static int count = 0;
    private static int call = 0;

    public static void main(String[] args) {

        System.out.println("Hello world");
        String userDirectory = Paths.get("")
                .toAbsolutePath()
                .toString();
        System.out.println(userDirectory);
        File inputFile = new File("vd012.xml");
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();

            NodeList nList = doc.getElementsByTagName("edge");
            System.out.println(nList.getLength());

            Document newDoc = dBuilder.newDocument();
            newDoc.appendChild(newDoc.createElement("routes"));
            Node root = newDoc.getDocumentElement();
            float M = 0;

            for (int i = 0; i < nList.getLength(); i++) {
                Node node = nList.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;
                    String id = element.getAttribute("id");
                    if (id.charAt(0) == 'E') {
                        float x = Float.parseFloat(id.substring(1));
                        if (x > M)
                            M = x;
                    }

                }
            }
            
            System.out.println("\n" + (nList.getLength()/2));

            for (int i = 0; i < nList.getLength(); i++) {
                Node node = nList.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;
                    String id = element.getAttribute("id");
                    if (id.charAt(0) == 'E' && id.charAt(1) != '0') {
                        float x = Float.parseFloat(id.substring(1));
                        Node personFlow1 = CreatePersonFlow(newDoc, x, "a", M, i % 40);
                        Node personFlow2 = CreatePersonFlow(newDoc, x, "b", M, i % 40);
                        root.appendChild(personFlow1);
                        root.appendChild(personFlow2);
                    }

                }
            }
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transf;
            try {
                transf = transformerFactory.newTransformer();
                transf.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
                transf.setOutputProperty(OutputKeys.INDENT, "yes");
                transf.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
                DOMSource source = new DOMSource(newDoc);

                File myFile = new File("vd012.rou.xml");

                StreamResult console = new StreamResult(System.out);
                StreamResult file = new StreamResult(myFile);

                transf.transform(source, console);
                transf.transform(source, file);
            } catch (TransformerException e) {
                e.printStackTrace();
            }

        } catch (ParserConfigurationException | SAXException | IOException e) {
            e.printStackTrace();
        }

    }

    static Node CreatePersonFlow(Document doc, float x, String tail, float M, int begin) {
    	if(call % 30 == 0 && call > 0)
    		count++;
        Element personFlow = doc.createElement("personFlow");
        String id = "p" + Integer.toString((int) x) + tail;
        personFlow.setAttribute("id", id);
        personFlow.setAttribute("begin", "" + count);
        personFlow.setAttribute("period", "" + (5 + (begin % 6)));
        //personFlow.setAttribute("id", id);

        double pXa = (x < (M / 2 + 1)) ? (x * 1.0 / (M / 2 + 1)) : (x * 1.0 / M);
        Element walk = doc.createElement("walk");
        personFlow.appendChild(walk);
        if (tail == "a") {
            personFlow.setAttribute("impatience", df.format(pXa));
            walk.setAttribute("from", "E" + Integer.toString((int) x));
            walk.setAttribute("to", "-E" + Integer.toString((int) x));
        }
        if (tail == "b") {
            personFlow.setAttribute("impatience", df.format(1 - pXa));
            walk.setAttribute("to", "E" + Integer.toString((int) x));
            walk.setAttribute("from", "-E" + Integer.toString((int) x));
        }
        call++;
    	

        return personFlow;
    }
}