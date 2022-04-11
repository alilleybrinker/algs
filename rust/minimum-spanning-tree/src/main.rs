use petgraph::{
    dot::Dot,
    graph::{Graph, NodeIndex},
    unionfind::UnionFind,
    visit::EdgeRef,
};
use std::cmp::Ordering;
use std::collections::BinaryHeap as PriorityQueue;
use std::ops::Not as _;

type MyGraph = Graph<&'static str, u8>;
type MinSpanTree = Graph<&'static str, u8>;

fn setup_graph() -> MyGraph {
    let mut graph = Graph::new();

    let a = graph.add_node("A");
    let b = graph.add_node("B");
    let c = graph.add_node("C");
    let d = graph.add_node("D");
    let e = graph.add_node("E");
    let f = graph.add_node("F");
    let g = graph.add_node("G");

    graph.add_edge(a, c, 7);
    graph.add_edge(a, d, 5);
    graph.add_edge(b, c, 8);
    graph.add_edge(b, e, 4);
    graph.add_edge(c, d, 9);
    graph.add_edge(c, e, 10);
    graph.add_edge(d, e, 15);
    graph.add_edge(d, f, 6);
    graph.add_edge(e, f, 12);
    graph.add_edge(g, f, 11);
    graph.add_edge(g, e, 13);

    graph
}

/// Get the minimum spanning tree for a graph.
///
/// Uses Kruskal's algorithm.
fn minimum_spanning_tree(graph: &MyGraph) -> MinSpanTree {
    /// Set up a priority queue with a bundle of edges.
    fn init_pq(graph: &MyGraph) -> PriorityQueue<Bundle> {
        let mut pq = PriorityQueue::new();

        for edge_ref in graph.edge_references() {
            let source = edge_ref.source();
            let target = edge_ref.target();
            let weight = edge_ref.weight();

            pq.push(Bundle {
                weight: *weight,
                source,
                target,
            })
        }

        pq
    }

    fn add_edge_and_nodes(mt: &mut MinSpanTree, graph: &MyGraph, b: Bundle) {
        // Check if the source node exists by label.
        // If it doesn't, create it and get the index.
        let source_idx = mt
            .node_indices()
            .find(|i| mt[*i] == graph[b.source])
            .unwrap_or_else(|| mt.add_node(graph[b.source]));

        // Same for target.
        let target_idx = mt
            .node_indices()
            .find(|i| mt[*i] == graph[b.target])
            .unwrap_or_else(|| mt.add_node(graph[b.target]));

        // Finally, add the edge.
        mt.add_edge(source_idx, target_idx, b.weight);
    }

    // Set up the data structures we need.
    let mut mt = MinSpanTree::new();
    let mut uf = UnionFind::new(graph.node_count());
    let mut pq = init_pq(graph);

    // Run Kruskal's algorithm.
    while mt.node_count() < graph.node_count() {
        if let Some(b) = pq.pop() {
            println!(
                "Found edge from {} to {} with weight {}",
                graph[b.source], graph[b.target], b.weight
            );

            let u = b.source.index();
            let v = b.target.index();

            if uf.equiv(u, v).not() {
                println!("No cycle would be created...");

                add_edge_and_nodes(&mut mt, graph, b);
                uf.union(u, v);
            } else {
                println!("Cycle would be created... Skipping.");
            }
        }
    }

    mt
}

fn main() {
    let graph = setup_graph();
    let min_tree = minimum_spanning_tree(&graph);

    println!("{}", Dot::new(&graph));
    println!("{}", Dot::new(&min_tree));
}

//---------------------------------------------------------------------------
// Helper code.

#[derive(Debug, Copy, Clone)]
struct Bundle {
    weight: u8,
    source: NodeIndex,
    target: NodeIndex,
}

impl PartialEq for Bundle {
    fn eq(&self, other: &Bundle) -> bool {
        self.weight == other.weight
    }
}

impl Eq for Bundle {}

impl PartialOrd for Bundle {
    fn partial_cmp(&self, other: &Bundle) -> Option<Ordering> {
        // The reverse is because Rust's priority queue type is
        // normally a max-heap, and we want a min-heap.
        Some(self.weight.cmp(&other.weight).reverse())
    }
}

impl Ord for Bundle {
    fn cmp(&self, other: &Bundle) -> Ordering {
        // SAFETY: The unwrap is fine because `partial_cmp`
        // unconditionally returns the `Some` variant.
        self.partial_cmp(other).unwrap()
    }
}
