---
title: 'OPSDN: an enhanced SDN simulation framework for OPNET Modeler'
tags:
  - Python
  - C/C++
  - OPNET
  - Software defined networking
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
Traditional SDN simulators/emulators like OPNET, Mininet [@mininet], Estinet[@estinet] and MaxiNet[@maxinet], cannot provide acceptable simulation capabilities in large-scale and/or high-traffic network scenarios due to different event scheduling system. We propose OPSDN, a simulation framework that unifies the evetlet[@eventlet] event scheduling of the existing Ryu controller framework with the traditional OPNET DES (Discrete Event Simulation) engine. In OPSDN, the SDN controller events are also triggered by the DES engine, ensuring the consistency of the simulation progress between the two sides, thus obtaining more accurate simulation results. Additionally, OPSDN provides Ryu-like APIs and can reuse part of the Ryu libraries. Our simulation results show that the OPSDN controller can achieve the same control effect as the typical Ryu controller, and avoid unexpected TCP retransmissions due to the inconsistent simulation speed. We hope OPSDN will help researchers achieve more accessible large-scale SDN network simulations. Detailed introduction and evaluation are included in @jia_opsdn_2022.

# Statement of need
OPSDN provides researchers with a network simulation framework that allows them to conduct large-scale SDN network simulations on laptop-level hardware and leverage the accurate simulation modelling capabilities provided by OPNET. Therefore, the main impacts of this software are as follows.

1.	A hybrid simulation framework for OPNET and Ryu-like controllers is proposed to provide a unified event scheduling mechanism based on OPNET DES engine, allowing OPNET and SDN controllers to simulate simultaneously and avoid simulation distortion caused by different event mechanisms. This allows researchers to perform accurate SDN network modelling and simulation without worrying about the simulation architecture.

2. It provides a large-scale simulation mechanism running in laptop-level hardware for SDN simulation, filling the lack of large-scale network simulation capability in various types of network simulation/emulation software. This software enables an acceptable system complexity and hardware cost for simulating the large-scale network simulation. Researchers are able to perform larger-scale simulations such as large-scale SDN data-center networks and large-scale SD-MANETs. In addition, this framework can also help researchers conduct research on scheduling algorithms and topology design with large bandwidth and high traffic, which are difficult to obtain accurate results in traditional environments due to several constraints.

3. Researchers are allowed to use Python as the programming language for controllers instead of C/C++, even running in OPNET. In addition, we provide a Ryu-like controller framework that provides APIs similar to Ryu, making it easy for controller developers to port existing Ryu Apps. Researchers could build controller algorithm prototypes rapidly.

4. The idea of combining the DES event mechanism with the event mechanism of controller frameworks such as Ryu presented in this software is general. This software verifies the feasibility of this idea, which means we can apply it to other DES-based simulation tools, such as NS3 and OMNET++, and provide more powerful tools for subsequent research and simulation of SDN.

# Acknowledgements

We acknowledge support from Beijing Credit Top Company Limited during the genesis of this project.

# References
