pipeline {
    agent {
      docker { image 'aabedraba/rsa' }
    }
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh 'cd build'
                echo 'In build folder. CMake in progress..'
                sh 'cmake ..'
                sh 'make check'
            }
        }
    }
}
