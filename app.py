import streamlit as st
import subprocess
import pandas as pd

st.set_page_config(page_title="Router Simulator", layout="wide")
st.title("Router Simulator UI")

# ------------------ Nodes Input ------------------
n_nodes = st.number_input("Number of nodes", min_value=2, max_value=20, value=4)

# Default node names A, B, C, ...
default_nodes = [chr(65+i) for i in range(n_nodes)]
nodes_input = st.text_input("Nodes (space separated)", value=" ".join(default_nodes))
nodes = nodes_input.strip().split()
if len(nodes) != n_nodes:
    st.warning("Number of nodes does not match the count. Adjust node names.")
    st.stop()

# ------------------ Links Input ------------------
m_links = st.number_input("Number of links", min_value=1, max_value=n_nodes*(n_nodes-1)//2, value=n_nodes)
st.write("Enter edges in the table below:")

# Create default link table
default_edges = []
for i in range(m_links):
    u = nodes[i % n_nodes]
    v = nodes[(i+1) % n_nodes]
    cost = i + 1
    default_edges.append([u, v, cost])

df_edges = pd.DataFrame(default_edges, columns=["From", "To", "Cost"])

edited_df = st.data_editor(df_edges, num_rows="dynamic")

# Highlight negative costs
def highlight_neg(val):
    color = 'red' if val < 0 else ''
    return f'background-color: {color}'

st.dataframe(edited_df.style.applymap(highlight_neg, subset=["Cost"]))

# ------------------ Run Simulator ------------------
if st.button("Run Routing Simulator"):
    # Write topology.txt
    with open("topology.txt", "w") as f:
        f.write(f"{n_nodes}\n")
        f.write(" ".join(nodes) + "\n")
        f.write(f"{len(edited_df)}\n")
        for idx, row in edited_df.iterrows():
            f.write(f"{row['From']} {row['To']} {row['Cost']}\n")

    # Run the C++ simulator
    try:
        result = subprocess.run(["./routing_sim.exe"], capture_output=True, text=True, check=True)
        st.subheader("Simulator Output")
        st.text(result.stdout)
    except subprocess.CalledProcessError as e:
        st.error(f"Simulator failed: {e.stderr}")
