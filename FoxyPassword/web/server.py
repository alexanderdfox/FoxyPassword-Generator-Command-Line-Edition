#!/usr/bin/env python3
"""
Simple HTTP server for FoxyPassword Generator Web Interface
Serves the secure password generator locally for testing and development.
"""

import http.server
import socketserver
import os
import sys
from pathlib import Path

class SecureHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    """Custom HTTP request handler with security headers."""
    
    def end_headers(self):
        # Add security headers
        self.send_header('X-Content-Type-Options', 'nosniff')
        self.send_header('X-Frame-Options', 'DENY')
        self.send_header('X-XSS-Protection', '1; mode=block')
        self.send_header('Referrer-Policy', 'strict-origin-when-cross-origin')
        self.send_header('Content-Security-Policy', 
                        "default-src 'self'; "
                        "script-src 'self' 'unsafe-inline'; "
                        "style-src 'self' 'unsafe-inline' https://fonts.googleapis.com; "
                        "font-src 'self' https://fonts.gstatic.com; "
                        "img-src 'self' data:; "
                        "connect-src 'self';")
        super().end_headers()
    
    def log_message(self, format, *args):
        """Custom logging to show requests."""
        print(f"[{self.log_date_time_string()}] {format % args}")

def main():
    """Main function to start the server."""
    
    # Get the directory where this script is located
    script_dir = Path(__file__).parent
    os.chdir(script_dir)
    
    # Check if required files exist
    required_files = ['index.html', 'styles.css', 'script.js']
    missing_files = [f for f in required_files if not Path(f).exists()]
    
    if missing_files:
        print(f"Error: Missing required files: {', '.join(missing_files)}")
        print("Please ensure all web files are present in the web directory.")
        sys.exit(1)
    
    # Server configuration
    PORT = 8080
    HOST = 'localhost'
    
    try:
        with socketserver.TCPServer((HOST, PORT), SecureHTTPRequestHandler) as httpd:
            print("=" * 60)
            print("🦊 FoxyPassword Generator - Web Interface")
            print("=" * 60)
            print(f"🌐 Server running at: http://{HOST}:{PORT}")
            print(f"📁 Serving files from: {script_dir.absolute()}")
            print("🔒 Security headers enabled")
            print("=" * 60)
            print("Press Ctrl+C to stop the server")
            print("=" * 60)
            
            httpd.serve_forever()
            
    except KeyboardInterrupt:
        print("\n🛑 Server stopped by user")
    except OSError as e:
        if e.errno == 48:  # Address already in use
            print(f"❌ Error: Port {PORT} is already in use")
            print(f"Try using a different port or stop the process using port {PORT}")
        else:
            print(f"❌ Error starting server: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"❌ Unexpected error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
