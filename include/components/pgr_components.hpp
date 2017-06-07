/*PGR-GNU*****************************************************************

Copyright (c) 2015 pgRouting developers
Mail: project@pgrouting.org

Copyright (c) 2015 Maoguang Wang 
xjtumg1007@gmail.com

------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

********************************************************************PGR-GNU*/

#ifndef INCLUDE_COMPONENTS_PGR_COMPONENTS_HPP_
#define INCLUDE_COMPONENTS_PGR_COMPONENTS_HPP_
#pragma once

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/connected_components.hpp>

#include <deque>
#include <set>
#include <vector>
#include <algorithm>

#include "cpp_common/basePath_SSEC.hpp"
#include "cpp_common/pgr_base_graph.hpp"
#if 0
#include "./../../common/src/signalhandler.h"
#endif


template < class G > class Pgr_components;
// user's functions
// for development

//******************************************

/*******************************************
 * reference: http://www.boost.org/doc/libs/1_46_0/libs/graph/doc/connected_components.html
 * IN: const Graph& g

    An undirected graph. The graph type must be a model of Vertex List Graph and Incidence Graph.
    Python: The parameter is named graph. 

 * OUT: ComponentMap c

    The algorithm computes how many connected components are in the graph, and assigning each component an integer label. The algorithm then records which component each vertex in the graph belongs to by recording the component number in the component property map. The ComponentMap type must be a model of Writable Property Map. The value type shouch be an integer type, preferably the same as the vertices_size_type of the graph. The key type must be the graph's vertex descriptor type.
    Python: Must be an vertex_int_map for the graph.
    Python default: graph.get_vertex_int_map("component") 
*******************************************/

template < class G >
class Pgr_components {
 public:
     typedef typename G::V V;

     //! @name Components 
     //@{
     //! one to one
     int components(
             G &graph);

 private:
     //! Call to Dijkstra  1 source to 1 target
     int dijkstra_1_to_1(
             G &graph);

     void clear() {
         predecessors.clear();
         nodesInDistance.clear();
     }

     //! @name members;
     //@{
     struct found_goals{};  //!< exception for termination
     std::vector< V > predecessors;
     std::deque< V > nodesInDistance;
     //@}

     //! @name Stopping classes
     //@{
     //! class for stopping when 1 target is found
     //@}
};


/******************** IMPLEMENTTION ******************/


//! Components
template < class G >
int
Pgr_components< G >::components(
        G &graph) {
    clear();

    // adjust predecessors and distances vectors
    predecessors.resize(graph.num_vertices());

    // perform the algorithm
    int numm = dijkstra_1_to_1(graph);

    // get the results
	return numm;
}

//! Call to Dijkstra  1 source to 1 target
template < class G >
int
Pgr_components< G >::dijkstra_1_to_1(
        G &graph) {
	int numm = boost::connected_components(graph.graph, &predecessors[0]);
    return numm;
}

#endif  // INCLUDE_DIJKSTRA_PGR_DIJKSTRA_HPP_
