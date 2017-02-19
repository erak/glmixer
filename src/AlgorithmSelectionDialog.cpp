/*
 * AlgorithmSelectionDialog.cpp
 *
 *  Created on: Feb 28, 2010
 *      Author: Herbelin
 *
 *  This file is part of GLMixer.
 *
 *   GLMixer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GLMixer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with GLMixer.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#include "AlgorithmSelectionDialog.moc"

#include "SourceDisplayWidget.h"
#include "AlgorithmSource.h"
#include "SizeSelectionWidget.h"


AlgorithmSelectionDialog::AlgorithmSelectionDialog(QWidget *parent) : QDialog(parent), s(0)
{
    setupUi(this);

    AlgorithmComboBox->clear();
    // create sources with selected algo
    for (int i = 0; i < AlgorithmSource::NONE; ++i)
    	AlgorithmComboBox->addItem(AlgorithmSource::getAlgorithmDescription(i));

    QObject::connect(sizeselection, SIGNAL(sizeChanged()), this, SLOT(updateSourcePreview()));

}

AlgorithmSelectionDialog::~AlgorithmSelectionDialog()
{
    if (s) delete s;
}

void AlgorithmSelectionDialog::showEvent(QShowEvent *e){

    updateSourcePreview();

	QWidget::showEvent(e);
}

void AlgorithmSelectionDialog::done(int r){

	if (preview)
		preview->setSource(0);
	if (s) {
		delete s;
		s = 0;
	}
	QDialog::done(r);
}


void AlgorithmSelectionDialog::updateSourcePreview(){

	if(s) {
		// remove source from preview: this deletes the texture in the preview
		preview->setSource(0);
		// delete the source:
		delete s;
        s = 0;
	}

	GLuint tex = preview->getNewTextureIndex();
	try {
		// create a new source with a new texture index and the new parameters
        s = new AlgorithmSource(AlgorithmComboBox->currentIndex(), tex, 0,
                                sizeselection->getWidth(), sizeselection->getHeight(),
                                getSelectedVariability(), getUpdatePeriod(),
                                !ignoreAlphaCheckbox->isChecked());

	} catch (AllocationException &e){
        qCritical() << "Error creating an Algorithm source; " << e.message();
		// free the OpenGL texture
		glDeleteTextures(1, &tex);
		// return an invalid pointer
		s = 0;
	}

	// apply the source to the preview
	preview->setSource(s);
    preview->playSource(true);
}

void AlgorithmSelectionDialog::on_AlgorithmComboBox_currentIndexChanged(int algo){
    updateSourcePreview();
}


void AlgorithmSelectionDialog::on_frequencySlider_valueChanged(int v){
    if (s)
        s->setPeriodicity(getUpdatePeriod());
}

void AlgorithmSelectionDialog::on_variabilitySlider_valueChanged(int v){
    if (s)
        s->setVariability( double ( v ) / 100.0);
}


void  AlgorithmSelectionDialog::on_customUpdateFrequency_toggled(bool flag){
	if (!flag)
		frequencySlider->setValue(40);
}

void AlgorithmSelectionDialog::on_ignoreAlphaCheckbox_toggled(bool on){
    if (s)
        s->setIgnoreAlpha(!on);
}


int AlgorithmSelectionDialog::getSelectedAlgorithmIndex(){

	return AlgorithmComboBox->currentIndex();
}


double AlgorithmSelectionDialog::getSelectedVariability(){

	return double(variabilitySlider->value()) / 100.0;
}


int AlgorithmSelectionDialog::getSelectedWidth(){

    return sizeselection->getWidth();
}


int AlgorithmSelectionDialog::getSelectedHeight(){

    return sizeselection->getHeight();
}

unsigned long  AlgorithmSelectionDialog::getUpdatePeriod(){

	if (!customUpdateFrequency->isChecked())
		return 0;
	else
		return (unsigned long) ( 1000000.0 / double(frequencySlider->value()));

}

bool AlgorithmSelectionDialog::getIngoreAlpha(){

	return !ignoreAlphaCheckbox->isChecked();
}
