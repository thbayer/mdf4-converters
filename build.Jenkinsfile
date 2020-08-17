#!/usr/bin/env groovy

properties([
    parameters([
        booleanParam(defaultValue: (BRANCH_NAME == "develop"), description: '''Do you want to deploy this build to the Artifactory?''', name: 'IsDeployToArtifactory'),
    ])
])


/**
Print the node and the workspace where the script is executed.
*/
def echoWorkspace()
{
    echo "Running on node ${env.NODE_NAME} in workspace ${env.WORKSPACE}."
}

pipeline {
    agent {
        docker { image 'buster:mdf4'}
    }

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
    post {
        always {
            echo 'This will always run'
        }
        success {
            echo 'This will run only if successful'
        }
        failure {
            echo 'This will run only if failed'
        }
        unstable {
            echo 'This will run only if the run was marked as unstable'
        }
        changed {
            echo 'This will run only if the state of the Pipeline has changed'
            echo 'For example, if the Pipeline was previously failing but is now successful'
        }
    }
}
