/*
 * View.cpp
 *
 *  Created on: May 21, 2011
 *      Author: bh
 */


#include <QMouseEvent>

#include "GeometryView.h"
#include "glmixer.h"


// maps for button and modifiers
QMap<View::UserInput,Qt::MouseButtons> View::_buttonmap = View::defaultMouseButtonsMap();
QMap<View::UserInput,Qt::KeyboardModifiers> View::_modifiermap = View::defaultModifiersMap();
bool View::zoomcentered = false;
double View::zoomspeed = 120.0;


#if QT_VERSION > 0x040602
#define QTMIDDLEBUTTON Qt::MiddleButton
#else
#define QTMIDDLEBUTTON Qt::MidButton
#endif

QDomElement View::getConfiguration(QDomDocument &doc) {
	QDomElement viewelem = doc.createElement("View");
	QDomElement z = doc.createElement("Zoom");
    z.setAttribute("value", QString::number(getZoom(),'f',4) );
	viewelem.appendChild(z);
	QDomElement pos = doc.createElement("Panning");
    pos.setAttribute("X", QString::number(getPanningX(),'f',4));
    pos.setAttribute("Y", QString::number(getPanningY(),'f',4));
	viewelem.appendChild(pos);

	return viewelem;
}

void View::setConfiguration(QDomElement xmlconfig) {
	setZoom(xmlconfig.firstChildElement("Zoom").attribute("value", "1").toFloat());
	setPanning(xmlconfig.firstChildElement("Panning").attribute("X", "0").toFloat(), xmlconfig.firstChildElement("Panning").attribute("Y", "0").toFloat());
}


void View::setPanning(double x, double y, double z) {
	panx = CLAMP(x, -maxpanx, maxpanx);
	pany = CLAMP(y, - maxpany, maxpany);
	if (z > 0)
		panz = CLAMP(z, - maxpanz, maxpanz);

	setModelview();
	modified = true;
}


bool View::keyPressEvent(QKeyEvent * event) {

    return false;
}

bool View::keyReleaseEvent(QKeyEvent * event) {

	return false;
}

void View::setAction(ActionType a){

	if (currentAction != View::SELECT)
		previousAction = currentAction;
	currentAction = a;
}

bool View::getSourcesAtCoordinates(int mouseX, int mouseY, bool flag){

    return false;
}

void View::coordinatesFromMouse(int mouseX, int mouseY, double *X, double *Y){

	double dum;
	gluUnProject((double) mouseX, (double) (viewport[3] - mouseY), 0.0,
	            modelview, projection, viewport, X, Y, &dum);

}


QString View::userInputLabel(View::UserInput ab, bool verbose){

	if (verbose) {
		switch(ab) {
		case INPUT_ZOOM:
			return QObject::tr("Zoom in a source or zoom out to get an overview.");
		case INPUT_CONTEXT_MENU:
			return QObject::tr("Show the context menu.");
		case INPUT_NAVIGATE:
			return QObject::tr("Navigate by dragging the background (the sources follow).");
		case INPUT_DRAG:
			return QObject::tr("Drag the background independently from the sources.");
		case INPUT_SELECT:
			return QObject::tr("Add a source to the selection.");
		case INPUT_TOOL:
			return QObject::tr("Use the current tool (grab, scale, etc.) on the whole selection.");
		case INPUT_TOOL_INDIVIDUAL:
			return QObject::tr("Use the current tool (grab, scale, etc.) on one source at a time.");
		default:
			return QObject::tr("Do Nothing");
		}
	} else {
		switch(ab) {
		case INPUT_ZOOM:
			return QObject::tr("Zoom");
		case INPUT_CONTEXT_MENU:
			return QObject::tr("Context\nmenu");
		case INPUT_NAVIGATE:
			return QObject::tr("Navigate");
		case INPUT_DRAG:
			return QObject::tr("Drag");
		case INPUT_SELECT:
			return QObject::tr("Select");
		case INPUT_TOOL:
			return QObject::tr("Tool");
		case INPUT_TOOL_INDIVIDUAL:
			return QObject::tr("Tool\n(individual)");
		default:
			return QObject::tr("Do Nothing");
		}
	}
}


QMap<int, int> View::getMouseButtonsMap(QMap<View::UserInput,Qt::MouseButtons> from)
{
	QMap<int, int> intmap;
	QMapIterator<View::UserInput,Qt::MouseButtons> i(from);
	while ( i.hasNext() ) {
		i.next();
		intmap[ (int) i.key() ] = int( i.value() );
	}

	return intmap;
}

QMap<int, int> View::getMouseModifiersMap(QMap<View::UserInput,Qt::KeyboardModifiers> from)
{
	QMap<int, int> intmap;
	QMapIterator<View::UserInput,Qt::KeyboardModifiers> i(from);
	while ( i.hasNext() ) {
		i.next();
		intmap[ (int) i.key() ] = int( i.value() );
	}

	return intmap;
}

void View::setMouseButtonsMap(QMap<int,int> m)
{
	QMapIterator<int,int> i(m);
	while ( i.hasNext() ) {
		i.next();
		 _buttonmap [ (View::UserInput) i.key() ] = Qt::MouseButtons(i.value());
    }
    _buttonmap[View::INPUT_NONE] = Qt::NoButton;
}

void View::setMouseModifiersMap(QMap<int,int> m)
{
	QMapIterator<int,int> i(m);
	while ( i.hasNext() ) {
		i.next();
	     _modifiermap [ (View::UserInput) i.key() ] = Qt::KeyboardModifiers(i.value());
    }
    _modifiermap[View::INPUT_NONE] = Qt::NoModifier;
}

QMap<View::UserInput,Qt::MouseButtons> View::defaultMouseButtonsMap()
{
	QMap<View::UserInput,Qt::MouseButtons> qbuttonmap;
	qbuttonmap[View::INPUT_TOOL] = Qt::LeftButton;
	qbuttonmap[View::INPUT_TOOL_INDIVIDUAL] = Qt::LeftButton;
    qbuttonmap[View::INPUT_NAVIGATE] = QTMIDDLEBUTTON;
    qbuttonmap[View::INPUT_DRAG] = QTMIDDLEBUTTON;
	qbuttonmap[View::INPUT_SELECT] = Qt::LeftButton;
    qbuttonmap[View::INPUT_CONTEXT_MENU] = Qt::RightButton;
    qbuttonmap[View::INPUT_ZOOM] = Qt::NoButton;
	return qbuttonmap;
}

QMap<View::UserInput,Qt::KeyboardModifiers> View::defaultModifiersMap()
{
	QMap<View::UserInput,Qt::KeyboardModifiers> qmodifiermap;
	qmodifiermap[View::INPUT_TOOL] = Qt::NoModifier;
	qmodifiermap[View::INPUT_TOOL_INDIVIDUAL] = Qt::ShiftModifier;
	qmodifiermap[View::INPUT_NAVIGATE] = Qt::NoModifier;
	qmodifiermap[View::INPUT_DRAG] = Qt::ShiftModifier;
	qmodifiermap[View::INPUT_SELECT] = Qt::ControlModifier;
    qmodifiermap[View::INPUT_CONTEXT_MENU] = Qt::NoModifier;
    qmodifiermap[View::INPUT_ZOOM] = Qt::NoModifier;
    return qmodifiermap;
}


bool View::isUserInput(QMouseEvent *event, UserInput ab)
{
	// NOT XOR is true when both are true or both are null
	return (  !(event->buttons() ^ _buttonmap[ab]) && !(QApplication::keyboardModifiers() ^ _modifiermap[ab] ) );
}


QString View::userInputDescription(View::UserInput ab, QMap<View::UserInput,Qt::MouseButtons> bm, QMap<View::UserInput,Qt::KeyboardModifiers> mm){

	QString text;

	if (mm[ab] & Qt::SHIFT)
		text.append("[SHIFT] + ");
	if (mm[ab] & Qt::ALT)
		text.append("[ALT] + ");

#ifdef Q_OS_MAC
	if (mm[ab] & Qt::META)
		text.append("[CTRL] + ");
	if (mm[ab] & Qt::CTRL)
		text.append("[CMD] + ");
#else
	if (mm[ab] & Qt::META)
		text.append("[WIN] + ");
	if (mm[ab] & Qt::CTRL)
		text.append("[CTRL] + ");
#endif

	if (bm[ab] & Qt::LeftButton )
		text.append("Left");
	if (bm[ab] & Qt::RightButton )
		text.append("Right");
	if (bm[ab] & QTMIDDLEBUTTON)
		text.append("Middle");
	if (bm[ab] & Qt::XButton1 )
		text.append("1st extra");
	if (bm[ab] & Qt::XButton2)
		text.append("2nd extra");

	if (text.isEmpty())
		text.append("Not attributed.");
	else
		text.append(" mouse button.");

	return text;
}

void View::setZoomSpeed(double zs){
	zoomspeed = CLAMP(zs, 20.0, 220.0);
}
double View::zoomSpeed(){
	return zoomspeed;
}
void View::setZoomCentered(bool on){
	zoomcentered = on;
}
bool View::zoomCentered(){
	return zoomcentered;
}

void SelectionArea::draw() {
	// The rectangle for selection
	if ( enabled ) {
		glColor4ub(COLOR_SELECTION_AREA, 25);
		double start[2], end[2];
		start[0] = area.topLeft().x();
		start[1] = area.topLeft().y();
		end[0] = area.bottomRight().x();
		end[1] = area.bottomRight().y();
		glRectdv(start, end);
		glLineWidth(0.5);
		glColor4ub(COLOR_SELECTION_AREA, 125);
		glBegin(GL_LINE_LOOP);
		glVertex3d(start[0], start[1], 0.0);
		glVertex3d(end[0], start[1], 0.0);
		glVertex3d(end[0], end[1], 0.0);
		glVertex3d(start[0], end[1], 0.0);
		glEnd();
	}
}


void SelectionArea::markStart(QPointF s){
	area.setTopLeft(s);
}

void SelectionArea::markEnd(QPointF e){
	area.setBottomRight(e);
}




