const abusiveWords = ["nigga", "abusiveWord2", "abusiveWord3"]; // Add more words as needed

document.getElementById('send-btn').addEventListener('click', sendMessage);
document.getElementById('upload-btn').addEventListener('click', () => document.getElementById('image-input').click());
document.getElementById('image-input').addEventListener('change', sendImage);
document.getElementById('camera-btn').addEventListener('click', startCamera);
document.getElementById('message-input').addEventListener('keydown', function (event) {
    if (event.key === 'Enter') {
        event.preventDefault();
        sendMessage();
    }
});

document.getElementById('dark-mode-toggle').addEventListener('click', toggleDarkMode);

const chatBox = document.getElementById('chat-box');

function sendMessage() {
    const input = document.getElementById('message-input');
    const message = input.value.trim();

    // Check for abusive words
    if (containsAbusiveWords(message)) {
        showWarning("Your message contains inappropriate language. Please remove the abusive words and try again.");
        return; // Prevent the message from being sent
    }

    if (message) {
        addMessage(message, 'user');
        input.value = '';
    }
}

// Function to check for abusive words
function containsAbusiveWords(message) {
    const lowerCaseMessage = message.toLowerCase();
    return abusiveWords.some((word) => lowerCaseMessage.includes(word));
}

// Function to show a warning message in the chat box
function showWarning(text) {
    const warningDiv = document.createElement('div');
    warningDiv.classList.add('warning-message');
    warningDiv.textContent = text;
    chatBox.appendChild(warningDiv);
    chatBox.scrollTop = chatBox.scrollHeight;

    // Remove the warning message after 5 seconds
    setTimeout(() => {
        warningDiv.classList.add('fade-out');
        setTimeout(() => warningDiv.remove(), 1000); // Wait for fade-out effect to complete
    }, 5000);
}

function sendImage(event) {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = function (e) {
            addImage(e.target.result, 'user');
        };
        reader.readAsDataURL(file);
    }
}

function addMessage(text, sender) {
    const messageDiv = document.createElement('div');
    messageDiv.classList.add('message', sender);
    messageDiv.textContent = text;
    chatBox.appendChild(messageDiv);
    chatBox.scrollTop = chatBox.scrollHeight;
}

function addImage(src, sender) {
    const img = document.createElement('img');
    img.src = src;
    img.style.maxWidth = '100%';
    img.style.borderRadius = '5px';
    const messageDiv = document.createElement('div');
    messageDiv.classList.add('message', sender);
    messageDiv.appendChild(img);
    chatBox.appendChild(messageDiv);
    chatBox.scrollTop = chatBox.scrollHeight;
}

function startCamera() {
    const video = document.getElementById('camera');
    const canvas = document.getElementById('canvas');

    if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
        navigator.mediaDevices.getUserMedia({ video: true }).then(function (stream) {
            video.srcObject = stream;
            video.style.display = 'block';

            video.addEventListener('click', function () {
                canvas.width = video.videoWidth;
                canvas.height = video.videoHeight;
                canvas.getContext('2d').drawImage(video, 0, 0);
                const dataURL = canvas.toDataURL('image/png');
                addImage(dataURL, 'user');
                stream.getTracks().forEach(track => track.stop());
                video.style.display = 'none';
            });
        }).catch(function (error) {
            alert('Unable to access camera: ' + error.message);
        });
    }
}

// Function to toggle dark mode
function toggleDarkMode() {
    const chatContainer = document.querySelector('.chat-container');
    chatContainer.classList.toggle('dark-mode');
}
