#!/usr/bin/env groovy

/**
Print the node and the workspace where the script is executed.
*/
def echoWorkspace()
{
    echo "Running on node ${env.NODE_NAME} in workspace ${env.WORKSPACE}."
}

pipeline {
    agent any

    stages {
        stage("Build and start test image") {
            steps {
                echoWorkspace()
                sh '''
                    mkdir build
                    cd build
                    cmake -DCMAKE_BUILD_TYPE=Release ..
                    make Boost_builder
                    make botan_builder
                    make fmt_builder
                    make heatshrink_builder
                    make tinyxml2_builder
                    cmake -DCMAKE_BUILD_TYPE=Release ..
                    make mdf2finalized
                '''
            }
        }
    }
}
