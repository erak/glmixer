/*
 * SourceSet.h
 *
 *  Created on: Dec 15, 2008
 *      Author: bh
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

#ifndef SOURCESET_H_
#define SOURCESET_H_

#include <set>
#include <deque>
#include <algorithm>

#include "Source.h"

typedef std::deque<SourceList> SourceListArray;


struct Source_distance_comp
{
    inline bool operator () (const Source *a, const Source *b) const
    {
        //Sort Furthest to Closest
        return (a && b && a->getDepth() < b->getDepth());
    }
};
typedef std::set<Source*, Source_distance_comp> SourceSet;

struct Source_distance_reverse_comp
{
    inline bool operator () (const Source *a, const Source *b) const
    {
        //Sort Closest to Furthest
        return (a && b && a->getDepth() > b->getDepth());
    }
};
typedef std::set<Source*, Source_distance_reverse_comp> reverseSourceSet;

struct hasId: public std::unary_function<Source*, bool>
{
    inline bool operator()(const Source* elem) const
    {
       return (elem && elem->getId() == _id);
    }

    hasId(GLuint id) : _id(id) { }

private:
    GLuint _id;

};


struct hasName: public std::unary_function<Source*, bool>
{
    inline bool operator()(const Source* elem) const
    {
       return (elem && elem->getName() == _n);
    }

    hasName(QString n) : _n(n) { }

private:
    QString _n;

};

struct isCloseTo: public std::unary_function<Source*, bool>
{
    inline bool operator()(const Source* elem) const
    {
       return ( elem && ABS(elem->getDepth() - _d) < DEPTH_EPSILON );
    }

    isCloseTo(GLdouble d) : _d(d) { }

private:
    GLdouble _d;

};


#endif /* SOURCESET_H_ */
