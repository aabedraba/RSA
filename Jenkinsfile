pipeline {
    agent {
      docker { image 'aabedraba/rsa' }
    }
    stages {
        stage('Build') {
            steps {
                sh 'echo 'Building..''
                sh 'cd build'
                sh 'echo 'In build folder. CMake in progress..''
                sh 'cmake ..'
                sh 'make'
            }
        }
    }
}
