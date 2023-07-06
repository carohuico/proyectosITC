from flask import Flask, render_template, request, jsonify
from flask_mysqldb import MySQL
app = Flask(__name__)
mysql = MySQL(app)


app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = '628630'
app.config['MYSQL_DB'] = 'Restaurante'

print("Conexion exitosa")

@app.route('/')
def inicio():
    return render_template('index.html')

@app.route('/admin')
def admin():
    return render_template('indAdmin.html')

@app.route('/sobre-nosotros')
def nosotros():
    return render_template('nosotros.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    elif request.method == 'POST':
        # Aquí puedes agregar la lógica para autenticar al usuario
        return inicio()

@app.route('/crearCuenta', methods=['GET', 'POST'])
def crearCuenta():
    if request.method == 'GET':
        return render_template('registrar.html')
    elif request.method == 'POST':
        # Aquí puedes agregar la lógica para procesar los datos del formulario
        return registroUsuario()

@app.route('/registrar', methods=['GET','POST'])
def registroUsuario():
    if request.method == 'GET':
        return "Registrar Usuario"
    if request.method == 'POST':
        user = request.form['usuario'] 
        pw = request.form['contraseña'] 
        name = request.form['nombre'] 
        lastname = request.form['apellido'] 
        tel = request.form['telefono'] 
        correo = request.form['email'] 
        cur = mysql.connection.cursor()
        cur.callproc('registroUsuario', [user, pw, name, lastname, tel, correo])
        mysql.connection.commit()
        cur.close()
        return login()        


@app.route('/auth', methods=['POST'])
def auth():
    usuario = request.form['usuario']
    contrasena = request.form['contrasena']

    cursor = db.cursor()
    resultado = cursor.callproc('sp_LoginUser', [usuario, contrasena, 0])
    valido = resultado[2]

    if valido == 1:
        return "Inicio de sesión exitoso"
    else:
        return "Usuario o contraseña incorrectos"

@app.route('/menu', methods=['GET'])
def menu():
    cur = mysql.connection.cursor()
    cur.callproc('ObtieneItems')
    productos = cur.fetchall()
    return render_template('menu.html', productos=productos)

@app.route('/historial', methods=['GET'])
def pagos():
    cur = mysql.connection.cursor()
    cur.callproc('obtenerPagos')
    pagos = cur.fetchall()
    return render_template('historial.html', pagos=pagos)

@app.route('/inventario', methods=['GET'])
def inventario():
    cur = mysql.connection.cursor()
    cur.callproc('ObtieneItemsInv')
    productos = cur.fetchall()
    return render_template('inventario.html', productos=productos)

@app.route('/producto/<int:id>', methods=['GET'])
def producto(id):
    cur = mysql.connection.cursor()
    cur.callproc('ObtieneItemInd', (id,))
    producto = cur.fetchone()
    if producto:
        return render_template('producto.html', producto=producto)
    else:
        return "Producto no encontrado"  # Otra acción adecuada en caso de que el producto no exista

@app.route('/reservacion')
def forma():
    return render_template('reservacion.html')

@app.route('/registrar_reserva', methods=['GET','POST'])
def reserva():
    if request.method == 'GET':
        return "Aqui es para insertar datos"
    if request.method == 'POST':
        num_personas = int(request.form['num-of-people'])
        fecha = request.form['reservation-date']
        hora = request.form['reservation-time']

        cursor = mysql.connection.cursor()
        cursor.callproc('RegistrarReserva', [num_personas, fecha, hora])
        mysql.connection.commit()
        cursor.close()
        return inicio()

@app.route('/agregar_resena/', methods=['POST'])
def resena(id):
    if request.method == 'GET':
        return "Aqui es para agregr reseñas"
    if request.method == 'POST':
        rating = request.form.get['puntuacion']
        nombreCliente = request.form['nombre']
        feedback = request.form['comentario']

        cursor = mysql.connection.cursor()
        cursor.callproc('AgregarResena', [id, rating, nombreCliente, feedback])
        mysql.connection.commit()
        cursor.close()
        return producto(id)

@app.route('/personal', methods=['GET','POST'])
def personal():
    cur = mysql.connection.cursor()
    cur.callproc('obtenerSucursales')
    sucursales = cur.fetchall()

    if request.method == 'POST':
        idSucursal = request.form['suc']
        cur.nextset()

        cur.callproc('obtenerEmp_Sucursales',[idSucursal])
        empleados = cur.fetchall()

        return render_template('personal.html', sucursales=sucursales, empleados=empleados)
    else:
        cur.close()
        return render_template('personal.html',sucursales=sucursales)

@app.route('/mesas', methods=['GET'])
def mesas():
    cur = mysql.connection.cursor()
    cur.callproc('ObtieneMesas')
    mesas  = cur.fetchall()
    return render_template('mesas.html', mesas=mesas)

@app.route('/actualizar_ganancias', methods=['GET', 'POST'])
def ganancias():
    if request.method == 'GET':
        return "Aqui es para insertar datos"
    if request.method == 'POST':
        mesa_id = int(request.form['mesa-id'])
        monto = int(request.form['monto'])
        cursor = mysql.connection.cursor()
        cursor.callproc('Ganancias', [mesa_id, monto])
        mysql.connection.commit()
        cursor.close()
        return mesas()

@app.route("/metodoPago")
def metodoPago():
    return render_template('Met-Pago.html')

@app.route("/pagar", methods=['GET','POST'])
def pagar():
    if request.method == 'GET':
        return "Aqui es para pagar"
    if request.method == 'POST':
        id_cliente = request.form["id_cliente"]
        tipo_pago = request.form["tipo_pago"]
        total = request.form["total"]
        fecha = request.form["fecha"]
        hora = request.form["hora"]
        id_pedido = request.form["id_pedido"]

        cursor = mysql.connection.cursor()
        cursor.callproc("AgregarPago", (id_cliente, tipo_pago, total, fecha, hora, id_pedido))
        mysql.connection.commit()
        cursor.close()
        return inicio()


@app.route("/pedido")
def pedidoO():
    return render_template("pedidolinea.html")

@app.route("/agregar_direccion", methods=['GET','POST'])
def direccion():
    if request.method == 'GET':
        return "Aqui es para poner tu Direccion"
    if request.method == 'POST':
        estado = request.form["estado"]
        ciudad = request.form["city"]
        cp = request.form["CP"]
        col = request.form["Colonia"]
        calle = request.form["Calle"]
        num = request.form["Num"]

        cursor = mysql.connection.cursor()
        cursor.callproc("AgregarDir", [estado, ciudad, cp, col, calle, num])
        mysql.connection.commit()
        cursor.close()
        return metodoPago()
    
if __name__ == '__main__':
    app.run(debug=True)
