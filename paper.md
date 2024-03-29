---
title: 'OPSDN: an enhanced SDN simulation framework for OPNET Modeler'
tags:
  - Python
  - C/C++
  - OPNET
  - Software-defined networking
  - network simulation
authors:
  - name: Zequn Jia
    orcid: 0000-0002-7144-4448
    affiliation: "1, 2" # (Multiple affiliations must be quoted)
    corresponding: true
  - name: Yantao Sun
    affiliation: 1
  - name: Qiang Liu
    affiliation: 1
affiliations:
 - name: School of Computer and Information Technology, Beijing Jiaotong University, Beijing, China.
   index: 1
 - name: School of Electrical and Data Engineering, University of Technology Sydney, Sydney, Australia.
   index: 2
date: 25 August 2022
bibliography: paper.bib

# Optional fields if submitting to a AAS journal too, see this blog post:
# https://blog.joss.theoj.org/2018/12/a-new-collaboration-with-aas-publishing
# aas-doi: 10.3847/xxxxx <- update this with the DOI from AAS once you know it.
# aas-journal: Astrophysical Journal <- The name of the AAS journal.
---

# Summary
Network testing environments are essential software packages in software-defined networking (SDN) research [@zavrak2017feature]. Traditional SDN testing tools include emulators like Mininet [@mininet] and simulators with SDN module support such as OPNET, NS3 [@ns3], and OMNET++ [@omnetpp]. However, both of these kinds of tools suffer from distortion when used for large-scale topology or high-traffic scenarios. The emulation of network devices typically requires heavy resources, making it difficult for emulators to support large-scale network simulations. For example, Mininet usually supports no more than 4096 network devices and its CPU and bandwidth are limited by a single server. Simulators can usually support larger-scale networks by reducing the simulation speed. However, OPNET needs an interface to connect the simulation to an external SDN controller, which requires the simulation speed to be strictly the same as real-world time. But simulation speed is generally slower than real-time in large-scale topologies due to hardware limitations.

To solve the problem above, we propose OPSDN, a simulation framework for OPNET that allows researchers to conduct *large-scale* SDN simulations in laptop-level hardware. Instead of an external controller, OPSDN integrates the controller into the simulation to accurately sync the time of switches and the controller. It also offers APIs similar to the popular SDN controller framework Ryu [@ryu]. Researchers can use familiar APIs to develop and port controller applications.
Our simulation results show that the OPSDN controller can achieve the same control capability as the Ryu controller, and avoid unexpected TCP retransmissions introduced by the inconsistent simulation speed. We hope OPSDN will help researchers achieve more accessible large-scale SDN network simulations. Detailed introduction and evaluation are included in @jia_opsdn_2022.



# Statement of need
OPSDN provides researchers with a network simulation framework that allows them to conduct large-scale SDN network simulations on laptop-level hardware and to leverage the accurate simulation modeling capabilities provided by OPNET. Therefore, the main impacts of this software are as follows.

1.	A hybrid simulation framework for OPNET and Ryu-like controllers provides a unified event scheduling mechanism based on OPNET's Discrete Event Simulation (DES) engine, allowing OPNET and SDN controllers to be simulated simultaneously and avoids simulation distortion caused by different event mechanisms. This allows researchers to perform accurate SDN network modeling and simulation without worrying about the simulation architecture.

2. It provides a large-scale simulation mechanism running on laptop-level hardware for SDN simulation, filling the lack of large-scale network simulation capability in various types of network simulation/emulation software. This software enables acceptable system complexity and hardware cost for large-scale network simulation. Researchers are able to perform larger-scale simulations such as for large-scale SDN data-center networks and large-scale software-defined mobile ad hoc networks. In addition, this framework can also help researchers conduct research on scheduling algorithms and topology design with large bandwidth and high traffic, cases for which it is difficult to obtain accurate results in traditional environments due to several constraints.

3. Researchers are allowed to use Python as the programming language for controllers instead of C/C++, even running in OPNET. In addition, we provide a Ryu-like controller framework that provides APIs similar to Ryu, making it easy for controller developers to port existing Ryu Apps. Researchers can rapidly build controller algorithm prototypes.

4. The idea of combining the DES event mechanism with the event mechanism of controller frameworks such as Ryu presented in this software is general. This software verifies the feasibility of this idea, which means we can apply it to other DES-based simulation tools, such as NS3 and OMNET++, and provide more powerful tools for subsequent research and simulation of SDN.

# Acknowledgements

We acknowledge support from Beijing Credit Top Company Limited during the genesis of this project.

# References
