#include <boost/graph/adjacency_list.hpp>
#include <string>
typedef std::string vertex_t;

typedef boost::adjacency_list<
    boost::vecS
    , boost::vecS
    , boost::bidirectionalS
    , vertex_t
> graph_type;

#include <iosfwd>

namespace detail {
    template <class GraphT>
    class vertex_writer {
        const GraphT& g_;

    public:
        explicit vertex_writer(const GraphT& g)
            : g_(g)
        {}

        template <class VertexDescriptorT>
        void operator()(
            std::ostream& out,
            const VertexDescriptorT& d) const
        {
            out << " [label=\""
                << boost::get(boost::vertex_bundle, g_)[d] 
                << "\"]"; 
        }
    }; // vertex_writer
} // namespace detail

#include <boost/graph/graphviz.hpp>

std::ostream& operator<<(std::ostream& out, const graph_type& g) {
    detail::vertex_writer<graph_type> vw(g);
    boost::write_graphviz(out, g, vw);

    return out;
}



int main() {
    graph_type graph;

    static const std::size_t vertex_count = 5;
    graph.m_vertices.reserve(vertex_count);
    /*
    C++ -> STL -> Boost -> C++ guru <- C
    */
    
    typedef boost::graph_traits<graph_type>::vertex_descriptor descriptor_t;
    descriptor_t cpp 
        = boost::add_vertex(vertex_t("C++"), graph);
    descriptor_t stl 
        = boost::add_vertex(vertex_t("STL"), graph);
    descriptor_t boost 
        = boost::add_vertex(vertex_t("Boost"), graph);
    descriptor_t guru 
        = boost::add_vertex(vertex_t("C++ guru"), graph);
    descriptor_t ansic 
        = boost::add_vertex(vertex_t("C"), graph);

    BOOST_STATIC_ASSERT((boost::is_same<descriptor_t, std::size_t>::value));

    boost::add_edge(cpp, stl, graph);
    boost::add_edge(stl, boost, graph);
    boost::add_edge(boost, guru, graph);
    boost::add_edge(ansic, guru, graph);

    std::cout << graph;
}
