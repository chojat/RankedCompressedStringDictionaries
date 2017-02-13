/* IteratorRankedDictStringVector.h
 * Copyright (C) 2016, Álvaro Alonso
 * all rights reserved.
 *
 * Iterator class for scanning a vector of strings.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 * Contacting the authors:
 *   Álvaro Alonso:  	alvaro.alonso.isla@alumnos.uva.es
 */

#ifndef _ITERATORRANKEDDICTSTRINGVECTOR_H
#define _ITERATORRANKEDDICTSTRINGVECTOR_H

#include <string.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class IteratorRankedDictStringVector : public IteratorRankedDictString 
{
	public:
		/** Constructor for the Vector Iterator:
		    @arr: the array of strings.
		    @elements: number of elements in the vector.
		*/
	    	IteratorRankedDictStringVector(vector<uchar*> *arr, size_t elements)
		{ 
			this->arr = *arr;
			this->elements = elements; 
			this->scanneable = 0;
			
			// Obtains the number of total bytes in the strings
			for (uint i=0; i<this->elements; i++)
				this->scanneable += 1+strlen((char*)this->arr[i]);

			this->processed = 0;
		}

		/** Extracts the next string in the stream. 
		    @param strLen pointer to the string length.
		    @returns the next string.
		*/
		unsigned char* next(uint *str_length) 
		{
			processed++;

			*str_length = strlen((char*)(arr[processed-1]));

			return arr[processed-1];
		}

		/** Checks for non-processed strings in the stream. 
		    @returns if remains non-processed strings. 
		*/
	    	bool hasNext()
		{
			return processed<elements;
		}

		/** Generic destructor. */
		~IteratorRankedDictStringVector() 
		{
		}

	protected:
	        vector<uchar*> arr;	// The array of strings
		uint elements;		// Number of elements in the vector

		bool static sorting(uchar *i, uchar *j)
		{
			if (strcmp((char*)i, (char*)j) < 0) return true;
			else return false;
		}

	        void sortstr()
	        {
	        	std::sort(arr.begin(), arr.end(), sorting);
	        }
};

#endif  
